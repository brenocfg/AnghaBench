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
struct udc {int /*<<< orphan*/  virt_addr; TYPE_1__* regs; int /*<<< orphan*/  driver; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  gadget; } ;
struct TYPE_3__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DEVCFG_SOFTRESET ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma_pools (struct udc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct udc*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct udc* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* udc ; 
 int /*<<< orphan*/  udc_remove (struct udc*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_pci_remove(struct pci_dev *pdev)
{
	struct udc		*dev;

	dev = pci_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);
	/* gadget driver must not be registered */
	if (WARN_ON(dev->driver))
		return;

	/* dma pool cleanup */
	free_dma_pools(dev);

	/* reset controller */
	writel(AMD_BIT(UDC_DEVCFG_SOFTRESET), &dev->regs->cfg);
	free_irq(pdev->irq, dev);
	iounmap(dev->virt_addr);
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	pci_disable_device(pdev);

	udc_remove(dev);
}