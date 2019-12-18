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
struct net_bridge {scalar_t__ stp_enabled; unsigned char topology_change; int forward_delay; unsigned long bridge_ageing_time; unsigned long ageing_time; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BR_KERNEL_STP ; 
 int __set_ageing_time (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*,unsigned long) ; 
 int /*<<< orphan*/  br_warn (struct net_bridge*,char*) ; 

void __br_set_topology_change(struct net_bridge *br, unsigned char val)
{
	unsigned long t;
	int err;

	if (br->stp_enabled == BR_KERNEL_STP && br->topology_change != val) {
		/* On topology change, set the bridge ageing time to twice the
		 * forward delay. Otherwise, restore its default ageing time.
		 */

		if (val) {
			t = 2 * br->forward_delay;
			br_debug(br, "decreasing ageing time to %lu\n", t);
		} else {
			t = br->bridge_ageing_time;
			br_debug(br, "restoring ageing time to %lu\n", t);
		}

		err = __set_ageing_time(br->dev, t);
		if (err)
			br_warn(br, "error offloading ageing time\n");
		else
			br->ageing_time = t;
	}

	br->topology_change = val;
}