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
 unsigned long get_symbol_pos (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_ksym_addr (unsigned long) ; 
 int /*<<< orphan*/  kallsyms_expand_symbol (int /*<<< orphan*/ ,char*,int) ; 
 int lookup_module_symbol_name (unsigned long,char*) ; 

int lookup_symbol_name(unsigned long addr, char *symname)
{
	symname[0] = '\0';
	symname[KSYM_NAME_LEN - 1] = '\0';

	if (is_ksym_addr(addr)) {
		unsigned long pos;

		pos = get_symbol_pos(addr, NULL, NULL);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       symname, KSYM_NAME_LEN);
		return 0;
	}
	/* See if it's in a module. */
	return lookup_module_symbol_name(addr, symname);
}