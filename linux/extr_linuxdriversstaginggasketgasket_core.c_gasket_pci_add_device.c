#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct pci_dev {struct device dev; } ;
struct gasket_internal_desc {int /*<<< orphan*/  class; struct gasket_driver_desc* driver_desc; } ;
struct gasket_driver_desc {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  devt; TYPE_2__* device; int /*<<< orphan*/  name; } ;
struct gasket_dev {TYPE_1__ dev_info; int /*<<< orphan*/  dev; struct pci_dev* pci_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex ; 
 int gasket_alloc_dev (struct gasket_internal_desc*,struct device*,struct gasket_dev**,char const*) ; 
 int /*<<< orphan*/  gasket_cleanup_pci (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_free_dev (struct gasket_dev*) ; 
 int gasket_setup_pci (struct pci_dev*,struct gasket_dev*) ; 
 int gasket_sysfs_create_entries (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int gasket_sysfs_create_mapping (TYPE_2__*,struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_sysfs_generic_attrs ; 
 int /*<<< orphan*/  gasket_sysfs_remove_mapping (TYPE_2__*) ; 
 struct gasket_internal_desc* lookup_internal_desc (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int gasket_pci_add_device(struct pci_dev *pci_dev,
			  struct gasket_dev **gasket_devp)
{
	int ret;
	const char *kobj_name = dev_name(&pci_dev->dev);
	struct gasket_internal_desc *internal_desc;
	struct gasket_dev *gasket_dev;
	const struct gasket_driver_desc *driver_desc;
	struct device *parent;

	pr_debug("add PCI device %s\n", kobj_name);

	mutex_lock(&g_mutex);
	internal_desc = lookup_internal_desc(pci_dev);
	mutex_unlock(&g_mutex);
	if (!internal_desc) {
		dev_err(&pci_dev->dev,
			"PCI add device called for unknown driver type\n");
		return -ENODEV;
	}

	driver_desc = internal_desc->driver_desc;

	parent = &pci_dev->dev;
	ret = gasket_alloc_dev(internal_desc, parent, &gasket_dev, kobj_name);
	if (ret)
		return ret;
	gasket_dev->pci_dev = pci_dev;
	if (IS_ERR_OR_NULL(gasket_dev->dev_info.device)) {
		pr_err("Cannot create %s device %s [ret = %ld]\n",
		       driver_desc->name, gasket_dev->dev_info.name,
		       PTR_ERR(gasket_dev->dev_info.device));
		ret = -ENODEV;
		goto fail1;
	}

	ret = gasket_setup_pci(pci_dev, gasket_dev);
	if (ret)
		goto fail2;

	ret = gasket_sysfs_create_mapping(gasket_dev->dev_info.device,
					  gasket_dev);
	if (ret)
		goto fail3;

	/*
	 * Once we've created the mapping structures successfully, attempt to
	 * create a symlink to the pci directory of this object.
	 */
	ret = sysfs_create_link(&gasket_dev->dev_info.device->kobj,
				&pci_dev->dev.kobj, dev_name(&pci_dev->dev));
	if (ret) {
		dev_err(gasket_dev->dev,
			"Cannot create sysfs pci link: %d\n", ret);
		goto fail3;
	}
	ret = gasket_sysfs_create_entries(gasket_dev->dev_info.device,
					  gasket_sysfs_generic_attrs);
	if (ret)
		goto fail4;

	*gasket_devp = gasket_dev;
	return 0;

fail4:
fail3:
	gasket_sysfs_remove_mapping(gasket_dev->dev_info.device);
fail2:
	gasket_cleanup_pci(gasket_dev);
	device_destroy(internal_desc->class, gasket_dev->dev_info.devt);
fail1:
	gasket_free_dev(gasket_dev);
	return ret;
}