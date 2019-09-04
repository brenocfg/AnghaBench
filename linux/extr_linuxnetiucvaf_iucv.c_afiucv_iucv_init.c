#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  bus; } ;
struct TYPE_11__ {int (* iucv_register ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* iucv_unregister ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  root; int /*<<< orphan*/  bus; } ;
struct TYPE_10__ {void (* release ) (struct device*) ;TYPE_4__* driver; int /*<<< orphan*/  parent; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* af_iucv_dev ; 
 TYPE_4__ af_iucv_driver ; 
 int /*<<< orphan*/  af_iucv_handler ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*) ; 
 int device_register (TYPE_1__*) ; 
 int driver_register (TYPE_4__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_4__*) ; 
 scalar_t__ kfree ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* pr_iucv ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afiucv_iucv_init(void)
{
	int err;

	err = pr_iucv->iucv_register(&af_iucv_handler, 0);
	if (err)
		goto out;
	/* establish dummy device */
	af_iucv_driver.bus = pr_iucv->bus;
	err = driver_register(&af_iucv_driver);
	if (err)
		goto out_iucv;
	af_iucv_dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!af_iucv_dev) {
		err = -ENOMEM;
		goto out_driver;
	}
	dev_set_name(af_iucv_dev, "af_iucv");
	af_iucv_dev->bus = pr_iucv->bus;
	af_iucv_dev->parent = pr_iucv->root;
	af_iucv_dev->release = (void (*)(struct device *))kfree;
	af_iucv_dev->driver = &af_iucv_driver;
	err = device_register(af_iucv_dev);
	if (err)
		goto out_iucv_dev;
	return 0;

out_iucv_dev:
	put_device(af_iucv_dev);
out_driver:
	driver_unregister(&af_iucv_driver);
out_iucv:
	pr_iucv->iucv_unregister(&af_iucv_handler, 0);
out:
	return err;
}