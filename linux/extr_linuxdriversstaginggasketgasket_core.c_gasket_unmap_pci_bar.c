#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct gasket_internal_desc {struct gasket_driver_desc* driver_desc; } ;
struct gasket_driver_desc {TYPE_1__* bar_descriptions; } ;
struct gasket_dev {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  dev; TYPE_2__* bar_data; struct gasket_internal_desc* internal_desc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * virt_base; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PCI_BAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_unmap_pci_bar(struct gasket_dev *dev, int bar_num)
{
	ulong base, bytes;
	struct gasket_internal_desc *internal_desc = dev->internal_desc;
	const struct gasket_driver_desc *driver_desc =
		internal_desc->driver_desc;

	if (driver_desc->bar_descriptions[bar_num].size == 0 ||
	    !dev->bar_data[bar_num].virt_base)
		return;

	if (driver_desc->bar_descriptions[bar_num].type != PCI_BAR)
		return;

	iounmap(dev->bar_data[bar_num].virt_base);
	dev->bar_data[bar_num].virt_base = NULL;

	base = pci_resource_start(dev->pci_dev, bar_num);
	if (!base) {
		dev_err(dev->dev, "cannot get PCI BAR%u base address\n",
			bar_num);
		return;
	}

	bytes = pci_resource_len(dev->pci_dev, bar_num);
	release_mem_region(base, bytes);
}