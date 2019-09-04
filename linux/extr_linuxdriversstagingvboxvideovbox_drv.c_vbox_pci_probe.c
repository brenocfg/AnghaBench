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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct drm_device {struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  driver ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct drm_device*) ; 
 int vbox_driver_load (struct drm_device*) ; 
 int /*<<< orphan*/  vbox_driver_unload (struct drm_device*) ; 

__attribute__((used)) static int vbox_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct drm_device *dev = NULL;
	int ret = 0;

	dev = drm_dev_alloc(&driver, &pdev->dev);
	if (IS_ERR(dev)) {
		ret = PTR_ERR(dev);
		goto err_drv_alloc;
	}

	ret = pci_enable_device(pdev);
	if (ret)
		goto err_pci_enable;

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	ret = vbox_driver_load(dev);
	if (ret)
		goto err_vbox_driver_load;

	ret = drm_dev_register(dev, 0);
	if (ret)
		goto err_drv_dev_register;

	return ret;

 err_drv_dev_register:
	vbox_driver_unload(dev);
 err_vbox_driver_load:
	pci_disable_device(pdev);
 err_pci_enable:
	drm_dev_put(dev);
 err_drv_alloc:
	return ret;
}