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
struct visor_device {int /*<<< orphan*/  device; scalar_t__ pending_msg_hdr; int /*<<< orphan*/  list_all; int /*<<< orphan*/  vbus_hdr_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLVM_BUS_DESTROY ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visorbus_response (struct visor_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void visorbus_remove_instance(struct visor_device *dev)
{
	/*
	 * Note that this will result in the release method for
	 * dev->dev being called, which will call
	 * visorbus_release_busdevice().  This has something to do with
	 * the put_device() done in device_unregister(), but I have never
	 * successfully been able to trace thru the code to see where/how
	 * release() gets called.  But I know it does.
	 */
	kfree(dev->vbus_hdr_info);
	list_del(&dev->list_all);
	if (dev->pending_msg_hdr)
		visorbus_response(dev, 0, CONTROLVM_BUS_DESTROY);
	device_unregister(&dev->device);
}