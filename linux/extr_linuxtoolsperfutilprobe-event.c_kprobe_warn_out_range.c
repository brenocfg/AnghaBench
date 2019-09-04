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
typedef  unsigned long u64 ;

/* Variables and functions */
 int kernel_get_symbol_address_by_name (char*,unsigned long*,int,int) ; 
 scalar_t__ kprobe_blacklist__listed (unsigned long) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 

__attribute__((used)) static bool kprobe_warn_out_range(const char *symbol, unsigned long address)
{
	u64 etext_addr = 0;
	int ret;

	/* Get the address of _etext for checking non-probable text symbol */
	ret = kernel_get_symbol_address_by_name("_etext", &etext_addr,
						false, false);

	if (ret == 0 && etext_addr < address)
		pr_warning("%s is out of .text, skip it.\n", symbol);
	else if (kprobe_blacklist__listed(address))
		pr_warning("%s is blacklisted function, skip it.\n", symbol);
	else
		return false;

	return true;
}