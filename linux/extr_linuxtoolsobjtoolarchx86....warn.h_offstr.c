#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct symbol {char* name; unsigned long offset; } ;
struct section {char* name; } ;

/* Variables and functions */
 struct symbol* find_containing_func (struct section*,unsigned long) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,unsigned long) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline char *offstr(struct section *sec, unsigned long offset)
{
	struct symbol *func;
	char *name, *str;
	unsigned long name_off;

	func = find_containing_func(sec, offset);
	if (func) {
		name = func->name;
		name_off = offset - func->offset;
	} else {
		name = sec->name;
		name_off = offset;
	}

	str = malloc(strlen(name) + 20);

	if (func)
		sprintf(str, "%s()+0x%lx", name, name_off);
	else
		sprintf(str, "%s+0x%lx", name, name_off);

	return str;
}