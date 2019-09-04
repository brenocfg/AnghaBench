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
struct xenbus_device {scalar_t__ state; int /*<<< orphan*/  nodename; scalar_t__ otherend; } ;
struct device_driver {int dummy; } ;
struct device {struct device_driver* driver; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 scalar_t__ XenbusStateConnected ; 
 int XenbusStateUnknown ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 
 int xenbus_read_driver_state (scalar_t__) ; 

__attribute__((used)) static int print_device_status(struct device *dev, void *data)
{
	struct xenbus_device *xendev = to_xenbus_device(dev);
	struct device_driver *drv = data;

	/* Is this operation limited to a particular driver? */
	if (drv && (dev->driver != drv))
		return 0;

	if (!dev->driver) {
		/* Information only: is this too noisy? */
		pr_info("Device with no driver: %s\n", xendev->nodename);
	} else if (xendev->state < XenbusStateConnected) {
		enum xenbus_state rstate = XenbusStateUnknown;
		if (xendev->otherend)
			rstate = xenbus_read_driver_state(xendev->otherend);
		pr_warn("Timeout connecting to device: %s (local state %d, remote state %d)\n",
			xendev->nodename, xendev->state, rstate);
	}

	return 0;
}