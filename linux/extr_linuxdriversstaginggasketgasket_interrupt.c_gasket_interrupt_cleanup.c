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
struct gasket_interrupt_data {int type; struct gasket_interrupt_data* msix_entries; struct gasket_interrupt_data* eventfd_ctxs; struct gasket_interrupt_data* interrupt_counts; } ;
struct gasket_dev {struct gasket_interrupt_data* interrupt_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  PCI_MSI 130 
#define  PCI_MSIX 129 
#define  PLATFORM_WIRE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gasket_interrupt_msix_cleanup (struct gasket_interrupt_data*) ; 
 int /*<<< orphan*/  kfree (struct gasket_interrupt_data*) ; 

void gasket_interrupt_cleanup(struct gasket_dev *gasket_dev)
{
	struct gasket_interrupt_data *interrupt_data =
		gasket_dev->interrupt_data;
	/*
	 * It is possible to get an error code from gasket_interrupt_init
	 * before interrupt_data has been allocated, so check it.
	 */
	if (!interrupt_data)
		return;

	switch (interrupt_data->type) {
	case PCI_MSIX:
		gasket_interrupt_msix_cleanup(interrupt_data);
		break;

	case PCI_MSI:
	case PLATFORM_WIRE:
	default:
		dev_dbg(gasket_dev->dev,
			"Cannot handle unsupported interrupt type %d\n",
			interrupt_data->type);
	}

	kfree(interrupt_data->interrupt_counts);
	kfree(interrupt_data->eventfd_ctxs);
	kfree(interrupt_data->msix_entries);
	kfree(interrupt_data);
	gasket_dev->interrupt_data = NULL;
}