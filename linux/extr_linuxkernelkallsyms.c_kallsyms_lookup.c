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
 char* bpf_address_lookup (unsigned long,unsigned long*,unsigned long*,char**,char*) ; 
 char* ftrace_mod_address_lookup (unsigned long,unsigned long*,unsigned long*,char**,char*) ; 
 int /*<<< orphan*/  get_symbol_offset (unsigned long) ; 
 unsigned long get_symbol_pos (unsigned long,unsigned long*,unsigned long*) ; 
 scalar_t__ is_ksym_addr (unsigned long) ; 
 int /*<<< orphan*/  kallsyms_expand_symbol (int /*<<< orphan*/ ,char*,int) ; 
 char* module_address_lookup (unsigned long,unsigned long*,unsigned long*,char**,char*) ; 

const char *kallsyms_lookup(unsigned long addr,
			    unsigned long *symbolsize,
			    unsigned long *offset,
			    char **modname, char *namebuf)
{
	const char *ret;

	namebuf[KSYM_NAME_LEN - 1] = 0;
	namebuf[0] = 0;

	if (is_ksym_addr(addr)) {
		unsigned long pos;

		pos = get_symbol_pos(addr, symbolsize, offset);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       namebuf, KSYM_NAME_LEN);
		if (modname)
			*modname = NULL;
		return namebuf;
	}

	/* See if it's in a module or a BPF JITed image. */
	ret = module_address_lookup(addr, symbolsize, offset,
				    modname, namebuf);
	if (!ret)
		ret = bpf_address_lookup(addr, symbolsize,
					 offset, modname, namebuf);

	if (!ret)
		ret = ftrace_mod_address_lookup(addr, symbolsize,
						offset, modname, namebuf);
	return ret;
}