/*
 *  dyldo is a dll injection strategy.
 *  Copyright (C) 2010-2011 Vikas Naresh Kumar
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __DYLDO_H__
#define __DYLDO_H__

#include <dyldo_config.h>

typedef union {
	enum {
		PTR_IS_32BIT,
		PTR_IS_64BIT
	} type;
	union u_ptr32or64_t {
		void *pv;
		uint32_t *p32;
		uint64_t *p64;
	} c;
} ptr32or64_t;

typedef struct dyldo_is_opaque dyldo_t;

/* create the dyldo object for the running process whose PID is given as an
 * argument. Returns a pointer to an opaque object that must be freed by
 * dyldo_delete() function later to conserve memory.
 */
dyldo_t *dyldo_create(pid_t);
/* delete memory and close all open handles related to the dyldo'ed process.
 * This can lead to the dyldo'ed process to be unstable if not done in the same
 * thread as create function above.
 */
void dyldo_destroy(dyldo_t *dyldo);
/* finds the symbol in the symbol table of executable and returns the memory
 * location of it. On a 64-bit system the running process can be 32 or 64 bit,
 * and hence they both need to be handled correctly or even simultaneously.
 */
ptr32or64_t *dyldo_read_symbol(dyldo_t *, const char *symbol);

int dyldo_insert(dyldo_t *dyldo, const char *dll, const char *symbol, void *arg);

#endif /* __DYLDO_H__ */
