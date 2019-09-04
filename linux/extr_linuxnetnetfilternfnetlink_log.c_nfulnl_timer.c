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
struct timer_list {int dummy; } ;
struct nfulnl_instance {int /*<<< orphan*/  lock; scalar_t__ skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfulnl_send (struct nfulnl_instance*) ; 
 struct nfulnl_instance* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nfulnl_instance* inst ; 
 int /*<<< orphan*/  instance_put (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
nfulnl_timer(struct timer_list *t)
{
	struct nfulnl_instance *inst = from_timer(inst, t, timer);

	spin_lock_bh(&inst->lock);
	if (inst->skb)
		__nfulnl_send(inst);
	spin_unlock_bh(&inst->lock);
	instance_put(inst);
}