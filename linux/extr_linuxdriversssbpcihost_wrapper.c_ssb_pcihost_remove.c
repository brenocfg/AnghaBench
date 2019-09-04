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
struct ssb_bus {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ssb_bus*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ssb_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_bus_unregister (struct ssb_bus*) ; 

__attribute__((used)) static void ssb_pcihost_remove(struct pci_dev *dev)
{
	struct ssb_bus *ssb = pci_get_drvdata(dev);

	ssb_bus_unregister(ssb);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kfree(ssb);
	pci_set_drvdata(dev, NULL);
}