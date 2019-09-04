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
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */

int pci_register_io_range(struct fwnode_handle *fwnode, phys_addr_t addr,
			resource_size_t	size)
{
	int ret = 0;
#ifdef PCI_IOBASE
	struct logic_pio_hwaddr *range;

	if (!size || addr + size < addr)
		return -EINVAL;

	range = kzalloc(sizeof(*range), GFP_ATOMIC);
	if (!range)
		return -ENOMEM;

	range->fwnode = fwnode;
	range->size = size;
	range->hw_start = addr;
	range->flags = LOGIC_PIO_CPU_MMIO;

	ret = logic_pio_register_range(range);
	if (ret)
		kfree(range);
#endif

	return ret;
}