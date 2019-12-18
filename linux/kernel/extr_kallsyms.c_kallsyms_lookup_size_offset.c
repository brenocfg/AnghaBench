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
 int /*<<< orphan*/  __bpf_address_lookup (unsigned long,unsigned long*,unsigned long*,char*) ; 
 int /*<<< orphan*/  get_symbol_pos (unsigned long,unsigned long*,unsigned long*) ; 
 scalar_t__ is_ksym_addr (unsigned long) ; 
 int /*<<< orphan*/  module_address_lookup (unsigned long,unsigned long*,unsigned long*,int /*<<< orphan*/ *,char*) ; 

int kallsyms_lookup_size_offset(unsigned long addr, unsigned long *symbolsize,
				unsigned long *offset)
{
	char namebuf[KSYM_NAME_LEN];

	if (is_ksym_addr(addr)) {
		get_symbol_pos(addr, symbolsize, offset);
		return 1;
	}
	return !!module_address_lookup(addr, symbolsize, offset, NULL, namebuf) ||
	       !!__bpf_address_lookup(addr, symbolsize, offset, namebuf);
}