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
struct skl_dev {int dummy; } ;
struct pci_dev {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 struct hdac_bus* pci_get_drvdata (struct pci_dev*) ; 
 int skl_suspend_late_dsp (struct skl_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int skl_suspend_late(struct device *dev)
{
	struct pci_dev *pci = to_pci_dev(dev);
	struct hdac_bus *bus = pci_get_drvdata(pci);
	struct skl_dev *skl = bus_to_skl(bus);

	return skl_suspend_late_dsp(skl);
}