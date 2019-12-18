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
struct TYPE_2__ {int /*<<< orphan*/  barrier_cpu_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  trace_rcu_barrier (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void rcu_barrier_trace(const char *s, int cpu, unsigned long done)
{
	trace_rcu_barrier(rcu_state.name, s, cpu,
			  atomic_read(&rcu_state.barrier_cpu_count), done);
}