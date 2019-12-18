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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_snd_front_info {TYPE_1__* xb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateClosing ; 
 unsigned int XenbusStateInitWait ; 
 int /*<<< orphan*/  XenbusStateUnknown ; 
 struct xen_snd_front_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_snd_drv_fini (struct xen_snd_front_info*) ; 
 int /*<<< orphan*/  xenbus_frontend_closed (struct xenbus_device*) ; 
 unsigned int xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_strstate (unsigned int) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_drv_remove(struct xenbus_device *dev)
{
	struct xen_snd_front_info *front_info = dev_get_drvdata(&dev->dev);
	int to = 100;

	xenbus_switch_state(dev, XenbusStateClosing);

	/*
	 * On driver removal it is disconnected from XenBus,
	 * so no backend state change events come via .otherend_changed
	 * callback. This prevents us from exiting gracefully, e.g.
	 * signaling the backend to free event channels, waiting for its
	 * state to change to XenbusStateClosed and cleaning at our end.
	 * Normally when front driver removed backend will finally go into
	 * XenbusStateInitWait state.
	 *
	 * Workaround: read backend's state manually and wait with time-out.
	 */
	while ((xenbus_read_unsigned(front_info->xb_dev->otherend, "state",
				     XenbusStateUnknown) != XenbusStateInitWait) &&
	       --to)
		msleep(10);

	if (!to) {
		unsigned int state;

		state = xenbus_read_unsigned(front_info->xb_dev->otherend,
					     "state", XenbusStateUnknown);
		pr_err("Backend state is %s while removing driver\n",
		       xenbus_strstate(state));
	}

	xen_snd_drv_fini(front_info);
	xenbus_frontend_closed(dev);
	return 0;
}