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
struct net_bridge {scalar_t__ stp_enabled; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ BR_NO_STP ; 
 scalar_t__ BR_USER_STP ; 
 int /*<<< orphan*/  br_err (struct net_bridge*,char*,int) ; 
 int /*<<< orphan*/  br_port_state_selection (struct net_bridge*) ; 
 int br_stp_call_user (struct net_bridge*,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_stp_stop(struct net_bridge *br)
{
	int err;

	if (br->stp_enabled == BR_USER_STP) {
		err = br_stp_call_user(br, "stop");
		if (err)
			br_err(br, "failed to stop userspace STP (%d)\n", err);

		/* To start timers on any ports left in blocking */
		spin_lock_bh(&br->lock);
		br_port_state_selection(br);
		spin_unlock_bh(&br->lock);
	}

	br->stp_enabled = BR_NO_STP;
}