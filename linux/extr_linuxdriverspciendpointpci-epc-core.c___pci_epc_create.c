#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_epc_ops {int dummy; } ;
struct TYPE_5__ {struct device* parent; int /*<<< orphan*/  class; } ;
struct pci_epc {TYPE_1__ dev; int /*<<< orphan*/  group; struct pci_epc_ops const* ops; int /*<<< orphan*/  pci_epf; int /*<<< orphan*/  lock; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct pci_epc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct pci_epc*) ; 
 struct pci_epc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ep_cfs_add_epc_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_epc_class ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct pci_epc *
__pci_epc_create(struct device *dev, const struct pci_epc_ops *ops,
		 struct module *owner)
{
	int ret;
	struct pci_epc *epc;

	if (WARN_ON(!dev)) {
		ret = -EINVAL;
		goto err_ret;
	}

	epc = kzalloc(sizeof(*epc), GFP_KERNEL);
	if (!epc) {
		ret = -ENOMEM;
		goto err_ret;
	}

	spin_lock_init(&epc->lock);
	INIT_LIST_HEAD(&epc->pci_epf);

	device_initialize(&epc->dev);
	epc->dev.class = pci_epc_class;
	epc->dev.parent = dev;
	epc->ops = ops;

	ret = dev_set_name(&epc->dev, "%s", dev_name(dev));
	if (ret)
		goto put_dev;

	ret = device_add(&epc->dev);
	if (ret)
		goto put_dev;

	epc->group = pci_ep_cfs_add_epc_group(dev_name(dev));

	return epc;

put_dev:
	put_device(&epc->dev);
	kfree(epc);

err_ret:
	return ERR_PTR(ret);
}