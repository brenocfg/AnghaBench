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
struct rcu_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  barrier_sequence; int /*<<< orphan*/  barrier_completion; int /*<<< orphan*/  barrier_cpu_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier_trace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_state ; 

__attribute__((used)) static void rcu_barrier_callback(struct rcu_head *rhp)
{
	if (atomic_dec_and_test(&rcu_state.barrier_cpu_count)) {
		rcu_barrier_trace(TPS("LastCB"), -1,
				   rcu_state.barrier_sequence);
		complete(&rcu_state.barrier_completion);
	} else {
		rcu_barrier_trace(TPS("CB"), -1, rcu_state.barrier_sequence);
	}
}