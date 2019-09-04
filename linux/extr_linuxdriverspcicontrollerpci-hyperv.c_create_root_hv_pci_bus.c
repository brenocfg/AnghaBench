#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * dev; } ;
struct hv_pcibus_device {int /*<<< orphan*/  state; TYPE_3__* pci_bus; TYPE_2__* hdev; TYPE_1__ msi_chip; int /*<<< orphan*/  resources_for_children; int /*<<< orphan*/  sysdata; } ;
struct TYPE_9__ {TYPE_1__* msi; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  hv_pci_assign_slots (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  hv_pcibus_installed ; 
 int /*<<< orphan*/  hv_pcifront_ops ; 
 int /*<<< orphan*/  pci_bus_add_devices (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_bus_assign_resources (TYPE_3__*) ; 
 TYPE_3__* pci_create_root_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_scan_child_bus (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 

__attribute__((used)) static int create_root_hv_pci_bus(struct hv_pcibus_device *hbus)
{
	/* Register the device */
	hbus->pci_bus = pci_create_root_bus(&hbus->hdev->device,
					    0, /* bus number is always zero */
					    &hv_pcifront_ops,
					    &hbus->sysdata,
					    &hbus->resources_for_children);
	if (!hbus->pci_bus)
		return -ENODEV;

	hbus->pci_bus->msi = &hbus->msi_chip;
	hbus->pci_bus->msi->dev = &hbus->hdev->device;

	pci_lock_rescan_remove();
	pci_scan_child_bus(hbus->pci_bus);
	pci_bus_assign_resources(hbus->pci_bus);
	hv_pci_assign_slots(hbus);
	pci_bus_add_devices(hbus->pci_bus);
	pci_unlock_rescan_remove();
	hbus->state = hv_pcibus_installed;
	return 0;
}