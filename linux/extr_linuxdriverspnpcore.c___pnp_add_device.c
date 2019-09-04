#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {TYPE_1__* protocol; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol_list; int /*<<< orphan*/  global_list; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* can_wakeup ) (struct pnp_dev*) ;int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_READY ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_delist_device (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_fixup_device (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_global ; 
 int /*<<< orphan*/  pnp_lock ; 
 int /*<<< orphan*/  stub1 (struct pnp_dev*) ; 

int __pnp_add_device(struct pnp_dev *dev)
{
	int ret;

	pnp_fixup_device(dev);
	dev->status = PNP_READY;

	mutex_lock(&pnp_lock);

	list_add_tail(&dev->global_list, &pnp_global);
	list_add_tail(&dev->protocol_list, &dev->protocol->devices);

	mutex_unlock(&pnp_lock);

	ret = device_register(&dev->dev);
	if (ret)
		pnp_delist_device(dev);
	else if (dev->protocol->can_wakeup)
		device_set_wakeup_capable(&dev->dev,
				dev->protocol->can_wakeup(dev));

	return ret;
}