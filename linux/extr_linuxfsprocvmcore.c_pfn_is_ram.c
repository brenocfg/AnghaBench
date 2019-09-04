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
 int oldmem_pfn_is_ram (unsigned long) ; 

__attribute__((used)) static int pfn_is_ram(unsigned long pfn)
{
	int (*fn)(unsigned long pfn);
	/* pfn is ram unless fn() checks pagetype */
	int ret = 1;

	/*
	 * Ask hypervisor if the pfn is really ram.
	 * A ballooned page contains no data and reading from such a page
	 * will cause high load in the hypervisor.
	 */
	fn = oldmem_pfn_is_ram;
	if (fn)
		ret = fn(pfn);

	return ret;
}