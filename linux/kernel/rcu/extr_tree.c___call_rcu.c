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
struct rcu_head {int /*<<< orphan*/ * next; scalar_t__ func; } ;
struct rcu_data {int /*<<< orphan*/  cblist; } ;
typedef  scalar_t__ rcu_callback_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCU_NOCB_CPU ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ RCU_SCHEDULER_INACTIVE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,struct rcu_head*,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __call_rcu_core (struct rcu_data*,struct rcu_head*,unsigned long) ; 
 int /*<<< orphan*/  __call_rcu_nocb_wake (struct rcu_data*,int,unsigned long) ; 
 scalar_t__ __is_kfree_rcu_offset (unsigned long) ; 
 scalar_t__ debug_rcu_head_queue (struct rcu_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rcu_data ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 int /*<<< orphan*/  rcu_leak_callback ; 
 scalar_t__ rcu_nocb_try_bypass (struct rcu_data*,struct rcu_head*,int*,unsigned long) ; 
 scalar_t__ rcu_scheduler_active ; 
 scalar_t__ rcu_segcblist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_enqueue (int /*<<< orphan*/ *,struct rcu_head*,int) ; 
 int /*<<< orphan*/  rcu_segcblist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_is_enabled (int /*<<< orphan*/ *) ; 
 int rcu_segcblist_is_offloaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_n_cbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_segcblist_n_lazy_cbs (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 
 struct rcu_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_callback (int /*<<< orphan*/ ,struct rcu_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rcu_kfree_callback (int /*<<< orphan*/ ,struct rcu_head*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
__call_rcu(struct rcu_head *head, rcu_callback_t func, bool lazy)
{
	unsigned long flags;
	struct rcu_data *rdp;
	bool was_alldone;

	/* Misaligned rcu_head! */
	WARN_ON_ONCE((unsigned long)head & (sizeof(void *) - 1));

	if (debug_rcu_head_queue(head)) {
		/*
		 * Probable double call_rcu(), so leak the callback.
		 * Use rcu:rcu_callback trace event to find the previous
		 * time callback was passed to __call_rcu().
		 */
		WARN_ONCE(1, "__call_rcu(): Double-freed CB %p->%pS()!!!\n",
			  head, head->func);
		WRITE_ONCE(head->func, rcu_leak_callback);
		return;
	}
	head->func = func;
	head->next = NULL;
	local_irq_save(flags);
	rdp = this_cpu_ptr(&rcu_data);

	/* Add the callback to our list. */
	if (unlikely(!rcu_segcblist_is_enabled(&rdp->cblist))) {
		// This can trigger due to call_rcu() from offline CPU:
		WARN_ON_ONCE(rcu_scheduler_active != RCU_SCHEDULER_INACTIVE);
		WARN_ON_ONCE(!rcu_is_watching());
		// Very early boot, before rcu_init().  Initialize if needed
		// and then drop through to queue the callback.
		if (rcu_segcblist_empty(&rdp->cblist))
			rcu_segcblist_init(&rdp->cblist);
	}
	if (rcu_nocb_try_bypass(rdp, head, &was_alldone, flags))
		return; // Enqueued onto ->nocb_bypass, so just leave.
	/* If we get here, rcu_nocb_try_bypass() acquired ->nocb_lock. */
	rcu_segcblist_enqueue(&rdp->cblist, head, lazy);
	if (__is_kfree_rcu_offset((unsigned long)func))
		trace_rcu_kfree_callback(rcu_state.name, head,
					 (unsigned long)func,
					 rcu_segcblist_n_lazy_cbs(&rdp->cblist),
					 rcu_segcblist_n_cbs(&rdp->cblist));
	else
		trace_rcu_callback(rcu_state.name, head,
				   rcu_segcblist_n_lazy_cbs(&rdp->cblist),
				   rcu_segcblist_n_cbs(&rdp->cblist));

	/* Go handle any RCU core processing required. */
	if (IS_ENABLED(CONFIG_RCU_NOCB_CPU) &&
	    unlikely(rcu_segcblist_is_offloaded(&rdp->cblist))) {
		__call_rcu_nocb_wake(rdp, was_alldone, flags); /* unlocks */
	} else {
		__call_rcu_core(rdp, head, flags);
		local_irq_restore(flags);
	}
}