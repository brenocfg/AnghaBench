#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct most_interface {int num_channels; int /*<<< orphan*/  dev; struct most_channel* p; int /*<<< orphan*/  description; } ;
struct TYPE_8__ {TYPE_3__* comp; } ;
struct TYPE_6__ {TYPE_1__* comp; } ;
struct most_channel {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; TYPE_4__ pipe1; TYPE_2__ pipe0; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  iface; struct most_channel** channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* disconnect_channel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* disconnect_channel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct most_channel*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_id ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void most_deregister_interface(struct most_interface *iface)
{
	int i;
	struct most_channel *c;

	pr_info("deregistering device %s (%s)\n", dev_name(&iface->dev),
		iface->description);
	for (i = 0; i < iface->num_channels; i++) {
		c = iface->p->channel[i];
		if (c->pipe0.comp)
			c->pipe0.comp->disconnect_channel(c->iface,
							c->channel_id);
		if (c->pipe1.comp)
			c->pipe1.comp->disconnect_channel(c->iface,
							c->channel_id);
		c->pipe0.comp = NULL;
		c->pipe1.comp = NULL;
		list_del(&c->list);
		device_unregister(&c->dev);
		kfree(c);
	}

	ida_simple_remove(&mdev_id, iface->p->dev_id);
	kfree(iface->p);
	device_unregister(&iface->dev);
}