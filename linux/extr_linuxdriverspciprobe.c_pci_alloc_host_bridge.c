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
struct TYPE_2__ {int /*<<< orphan*/  release; } ;
struct pci_host_bridge {int native_aer; int native_pcie_hotplug; int native_shpc_hotplug; int native_pme; int native_ltr; TYPE_1__ dev; int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pci_host_bridge* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_host_bridge_dev ; 

struct pci_host_bridge *pci_alloc_host_bridge(size_t priv)
{
	struct pci_host_bridge *bridge;

	bridge = kzalloc(sizeof(*bridge) + priv, GFP_KERNEL);
	if (!bridge)
		return NULL;

	INIT_LIST_HEAD(&bridge->windows);
	bridge->dev.release = pci_release_host_bridge_dev;

	/*
	 * We assume we can manage these PCIe features.  Some systems may
	 * reserve these for use by the platform itself, e.g., an ACPI BIOS
	 * may implement its own AER handling and use _OSC to prevent the
	 * OS from interfering.
	 */
	bridge->native_aer = 1;
	bridge->native_pcie_hotplug = 1;
	bridge->native_shpc_hotplug = 1;
	bridge->native_pme = 1;
	bridge->native_ltr = 1;

	return bridge;
}