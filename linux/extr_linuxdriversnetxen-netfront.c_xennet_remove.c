#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int /*<<< orphan*/  otherend; int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct netfront_info {TYPE_1__* netdev; scalar_t__ queues; } ;
struct TYPE_3__ {scalar_t__ reg_state; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 scalar_t__ XenbusStateClosed ; 
 scalar_t__ XenbusStateClosing ; 
 scalar_t__ XenbusStateUnknown ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct netfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_wq ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xenbus_read_driver_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,scalar_t__) ; 
 int /*<<< orphan*/  xennet_destroy_queues (struct netfront_info*) ; 
 int /*<<< orphan*/  xennet_disconnect_backend (struct netfront_info*) ; 
 int /*<<< orphan*/  xennet_free_netdev (TYPE_1__*) ; 

__attribute__((used)) static int xennet_remove(struct xenbus_device *dev)
{
	struct netfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "%s\n", dev->nodename);

	if (xenbus_read_driver_state(dev->otherend) != XenbusStateClosed) {
		xenbus_switch_state(dev, XenbusStateClosing);
		wait_event(module_wq,
			   xenbus_read_driver_state(dev->otherend) ==
			   XenbusStateClosing ||
			   xenbus_read_driver_state(dev->otherend) ==
			   XenbusStateUnknown);

		xenbus_switch_state(dev, XenbusStateClosed);
		wait_event(module_wq,
			   xenbus_read_driver_state(dev->otherend) ==
			   XenbusStateClosed ||
			   xenbus_read_driver_state(dev->otherend) ==
			   XenbusStateUnknown);
	}

	xennet_disconnect_backend(info);

	if (info->netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(info->netdev);

	if (info->queues) {
		rtnl_lock();
		xennet_destroy_queues(info);
		rtnl_unlock();
	}
	xennet_free_netdev(info->netdev);

	return 0;
}