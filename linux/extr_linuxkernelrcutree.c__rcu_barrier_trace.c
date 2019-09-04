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
struct rcu_state {int /*<<< orphan*/  barrier_cpu_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_barrier (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void _rcu_barrier_trace(struct rcu_state *rsp, const char *s,
			       int cpu, unsigned long done)
{
	trace_rcu_barrier(rsp->name, s, cpu,
			  atomic_read(&rsp->barrier_cpu_count), done);
}