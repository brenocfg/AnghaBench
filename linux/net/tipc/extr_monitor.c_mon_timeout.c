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
struct tipc_peer {int applied; } ;
struct tipc_monitor {scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; struct tipc_peer* self; int /*<<< orphan*/  peer_cnt; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int dom_size (int /*<<< orphan*/ ) ; 
 struct tipc_monitor* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct tipc_monitor* mon ; 
 int /*<<< orphan*/  mon_assign_roles (struct tipc_monitor*,struct tipc_peer*) ; 
 int /*<<< orphan*/  mon_update_local_domain (struct tipc_monitor*) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_timeout(struct timer_list *t)
{
	struct tipc_monitor *mon = from_timer(mon, t, timer);
	struct tipc_peer *self;
	int best_member_cnt = dom_size(mon->peer_cnt) - 1;

	write_lock_bh(&mon->lock);
	self = mon->self;
	if (self && (best_member_cnt != self->applied)) {
		mon_update_local_domain(mon);
		mon_assign_roles(mon, self);
	}
	write_unlock_bh(&mon->lock);
	mod_timer(&mon->timer, jiffies + mon->timer_intv);
}