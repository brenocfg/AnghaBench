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
struct pci_host_bridge {int /*<<< orphan*/  windows; int /*<<< orphan*/  (* release_fn ) (struct pci_host_bridge*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pci_host_bridge*) ; 
 struct pci_host_bridge* to_pci_host_bridge (struct device*) ; 

__attribute__((used)) static void devm_pci_release_host_bridge_dev(struct device *dev)
{
	struct pci_host_bridge *bridge = to_pci_host_bridge(dev);

	if (bridge->release_fn)
		bridge->release_fn(bridge);

	pci_free_resource_list(&bridge->windows);
}