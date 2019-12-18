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
struct logic_pio_hwaddr {scalar_t__ flags; scalar_t__ size; scalar_t__ hw_start; scalar_t__ io_start; } ;
struct fwnode_handle {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ LOGIC_PIO_CPU_MMIO ; 
 struct logic_pio_hwaddr* find_io_range_by_fwnode (struct fwnode_handle*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

unsigned long logic_pio_trans_hwaddr(struct fwnode_handle *fwnode,
				     resource_size_t addr, resource_size_t size)
{
	struct logic_pio_hwaddr *range;

	range = find_io_range_by_fwnode(fwnode);
	if (!range || range->flags == LOGIC_PIO_CPU_MMIO) {
		pr_err("IO range not found or invalid\n");
		return ~0UL;
	}
	if (range->size < size) {
		pr_err("resource size %pa cannot fit in IO range size %pa\n",
		       &size, &range->size);
		return ~0UL;
	}
	return addr - range->hw_start + range->io_start;
}