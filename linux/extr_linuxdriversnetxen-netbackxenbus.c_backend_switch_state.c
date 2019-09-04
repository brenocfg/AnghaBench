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
struct xenbus_device {int /*<<< orphan*/  nodename; } ;
struct backend_info {int state; int /*<<< orphan*/  have_hotplug_status_watch; struct xenbus_device* dev; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_strstate (int) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int) ; 

__attribute__((used)) static inline void backend_switch_state(struct backend_info *be,
					enum xenbus_state state)
{
	struct xenbus_device *dev = be->dev;

	pr_debug("%s -> %s\n", dev->nodename, xenbus_strstate(state));
	be->state = state;

	/* If we are waiting for a hotplug script then defer the
	 * actual xenbus state change.
	 */
	if (!be->have_hotplug_status_watch)
		xenbus_switch_state(dev, state);
}