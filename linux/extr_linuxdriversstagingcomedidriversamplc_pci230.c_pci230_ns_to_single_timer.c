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
 unsigned int pci230_choose_clk_count (unsigned int,unsigned int*,unsigned int) ; 
 unsigned int* pci230_timebase ; 

__attribute__((used)) static void pci230_ns_to_single_timer(unsigned int *ns, unsigned int flags)
{
	unsigned int count;
	unsigned int clk_src;

	clk_src = pci230_choose_clk_count(*ns, &count, flags);
	*ns = count * pci230_timebase[clk_src];
}