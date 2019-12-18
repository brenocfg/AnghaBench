#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  func; } ;
struct rcu_data {TYPE_2__ barrier_head; int /*<<< orphan*/  cblist; } ;
struct TYPE_5__ {int /*<<< orphan*/  barrier_sequence; int /*<<< orphan*/  barrier_cpu_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_rcu_head_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  debug_rcu_head_unqueue (TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rcu_data* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier_callback ; 
 int /*<<< orphan*/  rcu_barrier_trace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_data ; 
 int /*<<< orphan*/  rcu_nocb_flush_bypass (struct rcu_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_nocb_lock (struct rcu_data*) ; 
 int /*<<< orphan*/  rcu_nocb_unlock (struct rcu_data*) ; 
 scalar_t__ rcu_segcblist_entrain (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_state ; 

__attribute__((used)) static void rcu_barrier_func(void *unused)
{
	struct rcu_data *rdp = raw_cpu_ptr(&rcu_data);

	rcu_barrier_trace(TPS("IRQ"), -1, rcu_state.barrier_sequence);
	rdp->barrier_head.func = rcu_barrier_callback;
	debug_rcu_head_queue(&rdp->barrier_head);
	rcu_nocb_lock(rdp);
	WARN_ON_ONCE(!rcu_nocb_flush_bypass(rdp, NULL, jiffies));
	if (rcu_segcblist_entrain(&rdp->cblist, &rdp->barrier_head, 0)) {
		atomic_inc(&rcu_state.barrier_cpu_count);
	} else {
		debug_rcu_head_unqueue(&rdp->barrier_head);
		rcu_barrier_trace(TPS("IRQNQ"), -1,
				   rcu_state.barrier_sequence);
	}
	rcu_nocb_unlock(rdp);
}