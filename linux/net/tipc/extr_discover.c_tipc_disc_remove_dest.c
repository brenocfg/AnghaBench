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
struct tipc_discoverer {int num_nodes; int timer_intv; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int TIPC_DISC_FAST ; 
 int TIPC_DISC_INACTIVE ; 
 int TIPC_DISC_INIT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_disc_remove_dest(struct tipc_discoverer *d)
{
	int intv, num;

	spin_lock_bh(&d->lock);
	d->num_nodes--;
	num = d->num_nodes;
	intv = d->timer_intv;
	if (!num && (intv == TIPC_DISC_INACTIVE || intv > TIPC_DISC_FAST))  {
		d->timer_intv = TIPC_DISC_INIT;
		mod_timer(&d->timer, jiffies + d->timer_intv);
	}
	spin_unlock_bh(&d->lock);
}