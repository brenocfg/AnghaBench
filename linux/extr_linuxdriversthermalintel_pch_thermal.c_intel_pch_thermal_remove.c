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
struct pch_thermal_device {int /*<<< orphan*/  hw_base; int /*<<< orphan*/  tzd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pch_thermal_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pch_thermal_remove(struct pci_dev *pdev)
{
	struct pch_thermal_device *ptd = pci_get_drvdata(pdev);

	thermal_zone_device_unregister(ptd->tzd);
	iounmap(ptd->hw_base);
	pci_set_drvdata(pdev, NULL);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
}