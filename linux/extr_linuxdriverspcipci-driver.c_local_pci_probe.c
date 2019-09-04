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
struct pci_driver {int (* probe ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;
struct pci_dev {struct pci_driver* driver; struct device dev; } ;
struct drv_dev_and_id {int /*<<< orphan*/  id; struct pci_driver* drv; struct pci_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int stub1 (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long local_pci_probe(void *_ddi)
{
	struct drv_dev_and_id *ddi = _ddi;
	struct pci_dev *pci_dev = ddi->dev;
	struct pci_driver *pci_drv = ddi->drv;
	struct device *dev = &pci_dev->dev;
	int rc;

	/*
	 * Unbound PCI devices are always put in D0, regardless of
	 * runtime PM status.  During probe, the device is set to
	 * active and the usage count is incremented.  If the driver
	 * supports runtime PM, it should call pm_runtime_put_noidle(),
	 * or any other runtime PM helper function decrementing the usage
	 * count, in its probe routine and pm_runtime_get_noresume() in
	 * its remove routine.
	 */
	pm_runtime_get_sync(dev);
	pci_dev->driver = pci_drv;
	rc = pci_drv->probe(pci_dev, ddi->id);
	if (!rc)
		return rc;
	if (rc < 0) {
		pci_dev->driver = NULL;
		pm_runtime_put_sync(dev);
		return rc;
	}
	/*
	 * Probe function should return < 0 for failure, 0 for success
	 * Treat values > 0 as success, but warn.
	 */
	dev_warn(dev, "Driver probe function unexpectedly returned %d\n", rc);
	return 0;
}