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
struct net_bridge {unsigned long bridge_max_age; unsigned long max_age; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long BR_MAX_MAX_AGE ; 
 unsigned long BR_MIN_MAX_AGE ; 
 int ERANGE ; 
 scalar_t__ br_is_root_bridge (struct net_bridge*) ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_set_max_age(struct net_bridge *br, unsigned long val)
{
	unsigned long t = clock_t_to_jiffies(val);

	if (t < BR_MIN_MAX_AGE || t > BR_MAX_MAX_AGE)
		return -ERANGE;

	spin_lock_bh(&br->lock);
	br->bridge_max_age = t;
	if (br_is_root_bridge(br))
		br->max_age = br->bridge_max_age;
	spin_unlock_bh(&br->lock);
	return 0;

}