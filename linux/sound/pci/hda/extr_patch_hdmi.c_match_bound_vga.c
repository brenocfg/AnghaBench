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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct hdac_bus {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int match_bound_vga(struct device *dev, int subtype, void *data)
{
	struct hdac_bus *bus = data;
	struct pci_dev *pci, *master;

	if (!dev_is_pci(dev) || !dev_is_pci(bus->dev))
		return 0;
	master = to_pci_dev(bus->dev);
	pci = to_pci_dev(dev);
	return master->bus == pci->bus;
}