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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ supports_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cards_found ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pcipcwd_miscdev ; 
 int /*<<< orphan*/  pcipcwd_notifier ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pcipcwd_stop () ; 
 int /*<<< orphan*/  pcipcwd_temp_miscdev ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcipcwd_card_exit(struct pci_dev *pdev)
{
	/* Stop the timer before we leave */
	if (!nowayout)
		pcipcwd_stop();

	/* Deregister */
	misc_deregister(&pcipcwd_miscdev);
	if (pcipcwd_private.supports_temp)
		misc_deregister(&pcipcwd_temp_miscdev);
	unregister_reboot_notifier(&pcipcwd_notifier);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	cards_found--;
}