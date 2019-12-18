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

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 int /*<<< orphan*/  get_symbol_offset (unsigned long) ; 
 unsigned long get_symbol_pos (unsigned long,unsigned long*,unsigned long*) ; 
 scalar_t__ is_ksym_addr (unsigned long) ; 
 int /*<<< orphan*/  kallsyms_expand_symbol (int /*<<< orphan*/ ,char*,int) ; 
 int lookup_module_symbol_attrs (unsigned long,unsigned long*,unsigned long*,char*,char*) ; 

int lookup_symbol_attrs(unsigned long addr, unsigned long *size,
			unsigned long *offset, char *modname, char *name)
{
	name[0] = '\0';
	name[KSYM_NAME_LEN - 1] = '\0';

	if (is_ksym_addr(addr)) {
		unsigned long pos;

		pos = get_symbol_pos(addr, size, offset);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       name, KSYM_NAME_LEN);
		modname[0] = '\0';
		return 0;
	}
	/* See if it's in a module. */
	return lookup_module_symbol_attrs(addr, size, offset, modname, name);
}