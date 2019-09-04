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
struct net_bridge {unsigned long bridge_hello_time; unsigned long hello_time; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long BR_MAX_HELLO_TIME ; 
 unsigned long BR_MIN_HELLO_TIME ; 
 int ERANGE ; 
 scalar_t__ br_is_root_bridge (struct net_bridge*) ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_set_hello_time(struct net_bridge *br, unsigned long val)
{
	unsigned long t = clock_t_to_jiffies(val);

	if (t < BR_MIN_HELLO_TIME || t > BR_MAX_HELLO_TIME)
		return -ERANGE;

	spin_lock_bh(&br->lock);
	br->bridge_hello_time = t;
	if (br_is_root_bridge(br))
		br->hello_time = br->bridge_hello_time;
	spin_unlock_bh(&br->lock);
	return 0;
}