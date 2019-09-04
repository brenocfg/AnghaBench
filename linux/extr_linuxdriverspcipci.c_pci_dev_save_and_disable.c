#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_error_handlers {int /*<<< orphan*/  (* reset_prepare ) (struct pci_dev*) ;} ;
struct pci_dev {TYPE_1__* driver; } ;
struct TYPE_2__ {struct pci_error_handlers* err_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static void pci_dev_save_and_disable(struct pci_dev *dev)
{
	const struct pci_error_handlers *err_handler =
			dev->driver ? dev->driver->err_handler : NULL;

	/*
	 * dev->driver->err_handler->reset_prepare() is protected against
	 * races with ->remove() by the device lock, which must be held by
	 * the caller.
	 */
	if (err_handler && err_handler->reset_prepare)
		err_handler->reset_prepare(dev);

	/*
	 * Wake-up device prior to save.  PM registers default to D0 after
	 * reset and a simple register restore doesn't reliably return
	 * to a non-D0 state anyway.
	 */
	pci_set_power_state(dev, PCI_D0);

	pci_save_state(dev);
	/*
	 * Disable the device by clearing the Command register, except for
	 * INTx-disable which is set.  This not only disables MMIO and I/O port
	 * BARs, but also prevents the device from being Bus Master, preventing
	 * DMA from the device including MSI/MSI-X interrupts.  For PCI 2.3
	 * compliant devices, INTx-disable prevents legacy interrupts.
	 */
	pci_write_config_word(dev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE);
}