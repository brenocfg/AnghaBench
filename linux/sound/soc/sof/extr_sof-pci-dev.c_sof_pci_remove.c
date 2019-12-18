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

/* Variables and functions */
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sof_device_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sof_pci_remove(struct pci_dev *pci)
{
	/* call sof helper for DSP hardware remove */
	snd_sof_device_remove(&pci->dev);

	/* follow recommendation in pci-driver.c to increment usage counter */
	pm_runtime_get_noresume(&pci->dev);

	/* release pci regions and disable device */
	pci_release_regions(pci);
}