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
struct pci_dev {scalar_t__ device; int revision; int no_msi; scalar_t__ is_hotplug_bridge; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C ; 

__attribute__((used)) static void quirk_thunderbolt_hotplug_msi(struct pci_dev *pdev)
{
	if (pdev->is_hotplug_bridge &&
	    (pdev->device != PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C ||
	     pdev->revision <= 1))
		pdev->no_msi = 1;
}