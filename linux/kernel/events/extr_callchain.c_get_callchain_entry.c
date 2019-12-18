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
typedef  void perf_callchain_entry ;
struct callchain_cpus_entries {scalar_t__* cpu_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  callchain_cpus_entries ; 
 int /*<<< orphan*/  callchain_recursion ; 
 int get_recursion_context (int /*<<< orphan*/ ) ; 
 int perf_callchain_entry__sizeof () ; 
 struct callchain_cpus_entries* rcu_dereference (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct perf_callchain_entry *get_callchain_entry(int *rctx)
{
	int cpu;
	struct callchain_cpus_entries *entries;

	*rctx = get_recursion_context(this_cpu_ptr(callchain_recursion));
	if (*rctx == -1)
		return NULL;

	entries = rcu_dereference(callchain_cpus_entries);
	if (!entries)
		return NULL;

	cpu = smp_processor_id();

	return (((void *)entries->cpu_entries[cpu]) +
		(*rctx * perf_callchain_entry__sizeof()));
}