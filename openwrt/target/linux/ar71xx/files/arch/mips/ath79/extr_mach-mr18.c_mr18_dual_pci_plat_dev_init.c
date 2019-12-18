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
struct TYPE_4__ {int /*<<< orphan*/ * platform_data; } ;
struct pci_dev {TYPE_2__ dev; TYPE_1__* bus; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_main_wifi_data ; 
 int /*<<< orphan*/  pci_scan_wifi_data ; 

__attribute__((used)) static int mr18_dual_pci_plat_dev_init(struct pci_dev *dev)
{
	/* The PCIE devices are attached to different busses but they
	 * both share the same slot number. Checking the PCI_SLOT vals
	 * does not work.
	 */
	switch (dev->bus->number) {
	case 0:
		dev->dev.platform_data = &pci_main_wifi_data;
		break;
	case 1:
		dev->dev.platform_data = &pci_scan_wifi_data;
		break;
	}

	return 0;
}