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
struct net_bridge {unsigned long bridge_ageing_time; unsigned long ageing_time; int /*<<< orphan*/  gc_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */
 int __set_ageing_time (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long clock_t_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

int br_set_ageing_time(struct net_bridge *br, clock_t ageing_time)
{
	unsigned long t = clock_t_to_jiffies(ageing_time);
	int err;

	err = __set_ageing_time(br->dev, t);
	if (err)
		return err;

	spin_lock_bh(&br->lock);
	br->bridge_ageing_time = t;
	br->ageing_time = t;
	spin_unlock_bh(&br->lock);

	mod_delayed_work(system_long_wq, &br->gc_work, 0);

	return 0;
}