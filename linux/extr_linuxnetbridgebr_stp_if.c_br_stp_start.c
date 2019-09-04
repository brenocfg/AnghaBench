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
struct net_bridge {scalar_t__ bridge_forward_delay; int /*<<< orphan*/  lock; scalar_t__ hello_time; int /*<<< orphan*/  hello_timer; TYPE_1__* dev; int /*<<< orphan*/  stp_enabled; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_KERNEL_STP ; 
 scalar_t__ BR_MAX_FORWARD_DELAY ; 
 scalar_t__ BR_MIN_FORWARD_DELAY ; 
 int /*<<< orphan*/  BR_USER_STP ; 
 int ENOENT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  __br_set_forward_delay (struct net_bridge*,scalar_t__) ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*) ; 
 int /*<<< orphan*/  br_err (struct net_bridge*,char*,int) ; 
 int /*<<< orphan*/  br_port_state_selection (struct net_bridge*) ; 
 int br_stp_call_user (struct net_bridge*,char*) ; 
 int /*<<< orphan*/  dev_net (TYPE_1__*) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_stp_start(struct net_bridge *br)
{
	int err = -ENOENT;

	if (net_eq(dev_net(br->dev), &init_net))
		err = br_stp_call_user(br, "start");

	if (err && err != -ENOENT)
		br_err(br, "failed to start userspace STP (%d)\n", err);

	spin_lock_bh(&br->lock);

	if (br->bridge_forward_delay < BR_MIN_FORWARD_DELAY)
		__br_set_forward_delay(br, BR_MIN_FORWARD_DELAY);
	else if (br->bridge_forward_delay > BR_MAX_FORWARD_DELAY)
		__br_set_forward_delay(br, BR_MAX_FORWARD_DELAY);

	if (!err) {
		br->stp_enabled = BR_USER_STP;
		br_debug(br, "userspace STP started\n");
	} else {
		br->stp_enabled = BR_KERNEL_STP;
		br_debug(br, "using kernel STP\n");

		/* To start timers on any ports left in blocking */
		if (br->dev->flags & IFF_UP)
			mod_timer(&br->hello_timer, jiffies + br->hello_time);
		br_port_state_selection(br);
	}

	spin_unlock_bh(&br->lock);
}