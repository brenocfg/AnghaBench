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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_count ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  temp_miscdev ; 
 int type ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdtpci_miscdev ; 
 int /*<<< orphan*/  wdtpci_notifier ; 

__attribute__((used)) static void wdtpci_remove_one(struct pci_dev *pdev)
{
	/* here we assume only one device will ever have
	 * been picked up and registered by probe function */
	misc_deregister(&wdtpci_miscdev);
	if (type == 501)
		misc_deregister(&temp_miscdev);
	unregister_reboot_notifier(&wdtpci_notifier);
	free_irq(irq, &wdtpci_miscdev);
	pci_release_region(pdev, 2);
	pci_disable_device(pdev);
	dev_count--;
}