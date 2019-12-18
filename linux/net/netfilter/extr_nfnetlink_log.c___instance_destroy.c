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
struct nfulnl_instance {int /*<<< orphan*/  lock; scalar_t__ skb; int /*<<< orphan*/  copy_mode; int /*<<< orphan*/  hlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFULNL_COPY_DISABLED ; 
 int /*<<< orphan*/  __nfulnl_flush (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instance_put (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__instance_destroy(struct nfulnl_instance *inst)
{
	/* first pull it out of the global list */
	hlist_del_rcu(&inst->hlist);

	/* then flush all pending packets from skb */

	spin_lock(&inst->lock);

	/* lockless readers wont be able to use us */
	inst->copy_mode = NFULNL_COPY_DISABLED;

	if (inst->skb)
		__nfulnl_flush(inst);
	spin_unlock(&inst->lock);

	/* and finally put the refcount */
	instance_put(inst);
}