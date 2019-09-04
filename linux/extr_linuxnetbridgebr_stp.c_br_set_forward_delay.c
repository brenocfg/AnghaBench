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
 unsigned long BR_MAX_FORWARD_DELAY ; 
 unsigned long BR_MIN_FORWARD_DELAY ; 
 scalar_t__ BR_NO_STP ; 
 int ERANGE ; 
 int /*<<< orphan*/  __br_set_forward_delay (struct net_bridge*,unsigned long) ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_set_forward_delay(struct net_bridge *br, unsigned long val)
{
	unsigned long t = clock_t_to_jiffies(val);
	int err = -ERANGE;

	spin_lock_bh(&br->lock);
	if (br->stp_enabled != BR_NO_STP &&
	    (t < BR_MIN_FORWARD_DELAY || t > BR_MAX_FORWARD_DELAY))
		goto unlock;

	__br_set_forward_delay(br, t);
	err = 0;

unlock:
	spin_unlock_bh(&br->lock);
	return err;
}