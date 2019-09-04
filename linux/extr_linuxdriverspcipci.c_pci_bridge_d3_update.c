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
struct pci_dev {int bridge_d3; int /*<<< orphan*/  subordinate; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bridge_d3_possible (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_check_d3cold (struct pci_dev*,int*) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_walk_bus (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct pci_dev*,int*),int*) ; 

void pci_bridge_d3_update(struct pci_dev *dev)
{
	bool remove = !device_is_registered(&dev->dev);
	struct pci_dev *bridge;
	bool d3cold_ok = true;

	bridge = pci_upstream_bridge(dev);
	if (!bridge || !pci_bridge_d3_possible(bridge))
		return;

	/*
	 * If D3 is currently allowed for the bridge, removing one of its
	 * children won't change that.
	 */
	if (remove && bridge->bridge_d3)
		return;

	/*
	 * If D3 is currently allowed for the bridge and a child is added or
	 * changed, disallowance of D3 can only be caused by that child, so
	 * we only need to check that single device, not any of its siblings.
	 *
	 * If D3 is currently not allowed for the bridge, checking the device
	 * first may allow us to skip checking its siblings.
	 */
	if (!remove)
		pci_dev_check_d3cold(dev, &d3cold_ok);

	/*
	 * If D3 is currently not allowed for the bridge, this may be caused
	 * either by the device being changed/removed or any of its siblings,
	 * so we need to go through all children to find out if one of them
	 * continues to block D3.
	 */
	if (d3cold_ok && !bridge->bridge_d3)
		pci_walk_bus(bridge->subordinate, pci_dev_check_d3cold,
			     &d3cold_ok);

	if (bridge->bridge_d3 != d3cold_ok) {
		bridge->bridge_d3 = d3cold_ok;
		/* Propagate change to upstream bridges */
		pci_bridge_d3_update(bridge);
	}
}