#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rcu_state {int /*<<< orphan*/  barrier_sequence; int /*<<< orphan*/  barrier_cpu_count; int /*<<< orphan*/  rda; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct rcu_data {TYPE_1__ barrier_head; int /*<<< orphan*/  cblist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  _rcu_barrier_trace (struct rcu_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_rcu_head_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_rcu_head_unqueue (TYPE_1__*) ; 
 struct rcu_data* raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier_callback ; 
 scalar_t__ rcu_segcblist_entrain (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcu_barrier_func(void *type)
{
	struct rcu_state *rsp = type;
	struct rcu_data *rdp = raw_cpu_ptr(rsp->rda);

	_rcu_barrier_trace(rsp, TPS("IRQ"), -1, rsp->barrier_sequence);
	rdp->barrier_head.func = rcu_barrier_callback;
	debug_rcu_head_queue(&rdp->barrier_head);
	if (rcu_segcblist_entrain(&rdp->cblist, &rdp->barrier_head, 0)) {
		atomic_inc(&rsp->barrier_cpu_count);
	} else {
		debug_rcu_head_unqueue(&rdp->barrier_head);
		_rcu_barrier_trace(rsp, TPS("IRQNQ"), -1,
				   rsp->barrier_sequence);
	}
}