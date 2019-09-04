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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct esb_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  base; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 struct esb_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esb_remove(struct pci_dev *pdev)
{
	struct esb_dev *edev = dev_get_drvdata(&pdev->dev);

	watchdog_unregister_device(&edev->wdd);
	iounmap(edev->base);
	pci_release_region(edev->pdev, 0);
	pci_disable_device(edev->pdev);
}