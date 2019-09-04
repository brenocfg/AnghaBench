#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * bus; } ;
struct virtio_device {int index; int config_enabled; int config_change_pending; TYPE_2__ dev; int /*<<< orphan*/  vqs; TYPE_1__* config; int /*<<< orphan*/  config_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_S_ACKNOWLEDGE ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_S_FAILED ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_add_status (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_bus ; 
 int /*<<< orphan*/  virtio_index_ida ; 

int register_virtio_device(struct virtio_device *dev)
{
	int err;

	dev->dev.bus = &virtio_bus;
	device_initialize(&dev->dev);

	/* Assign a unique device index and hence name. */
	err = ida_simple_get(&virtio_index_ida, 0, 0, GFP_KERNEL);
	if (err < 0)
		goto out;

	dev->index = err;
	dev_set_name(&dev->dev, "virtio%u", dev->index);

	spin_lock_init(&dev->config_lock);
	dev->config_enabled = false;
	dev->config_change_pending = false;

	/* We always start by resetting the device, in case a previous
	 * driver messed it up.  This also tests that code path a little. */
	dev->config->reset(dev);

	/* Acknowledge that we've seen the device. */
	virtio_add_status(dev, VIRTIO_CONFIG_S_ACKNOWLEDGE);

	INIT_LIST_HEAD(&dev->vqs);

	/*
	 * device_add() causes the bus infrastructure to look for a matching
	 * driver.
	 */
	err = device_add(&dev->dev);
	if (err)
		ida_simple_remove(&virtio_index_ida, dev->index);
out:
	if (err)
		virtio_add_status(dev, VIRTIO_CONFIG_S_FAILED);
	return err;
}