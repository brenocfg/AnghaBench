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
struct uio_info {scalar_t__ priv; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_DISABLE ; 
 scalar_t__ INT_ENABLE_ADDR ; 
 scalar_t__ INT_MASK_ADDR ; 
 scalar_t__ MAILBOX ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct uio_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_info*) ; 

__attribute__((used)) static void remove(struct pci_dev *pdev)
{
	struct uio_info *info = pci_get_drvdata(pdev);

	/* disable interrupts */
	iowrite8(INT_DISABLE, info->priv + INT_MASK_ADDR);
	iowrite32(INT_DISABLE, info->priv + INT_ENABLE_ADDR);
	/* read mailbox to ensure board drops irq */
	ioread8(info->priv + MAILBOX);

	uio_unregister_device(info);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	iounmap(info->priv);

	kfree(info);
}