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
struct pci_epf_driver {int (* probe ) (struct pci_epf*) ;} ;
struct pci_epf {struct pci_epf_driver* driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct pci_epf*) ; 
 struct pci_epf* to_pci_epf (struct device*) ; 
 struct pci_epf_driver* to_pci_epf_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_epf_device_probe(struct device *dev)
{
	struct pci_epf *epf = to_pci_epf(dev);
	struct pci_epf_driver *driver = to_pci_epf_driver(dev->driver);

	if (!driver->probe)
		return -ENODEV;

	epf->driver = driver;

	return driver->probe(epf);
}