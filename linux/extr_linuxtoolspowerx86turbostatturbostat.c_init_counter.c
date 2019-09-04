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
struct thread_data {int cpu_id; int /*<<< orphan*/  flags; } ;
struct pkg_data {int package_id; } ;
struct core_data {int core_id; } ;
struct TYPE_2__ {int physical_package_id; int logical_node_id; int physical_core_id; int thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_IS_FIRST_CORE_IN_PACKAGE ; 
 int /*<<< orphan*/  CPU_IS_FIRST_THREAD_IN_CORE ; 
 struct core_data* GET_CORE (struct core_data*,int,int,int) ; 
 struct pkg_data* GET_PKG (struct pkg_data*,int) ; 
 struct thread_data* GET_THREAD (struct thread_data*,int,int,int,int) ; 
 scalar_t__ cpu_is_first_core_in_package (int) ; 
 TYPE_1__* cpus ; 

void init_counter(struct thread_data *thread_base, struct core_data *core_base,
	struct pkg_data *pkg_base, int cpu_id)
{
	int pkg_id = cpus[cpu_id].physical_package_id;
	int node_id = cpus[cpu_id].logical_node_id;
	int core_id = cpus[cpu_id].physical_core_id;
	int thread_id = cpus[cpu_id].thread_id;
	struct thread_data *t;
	struct core_data *c;
	struct pkg_data *p;


	/* Workaround for systems where physical_node_id==-1
	 * and logical_node_id==(-1 - topo.num_cpus)
	 */
	if (node_id < 0)
		node_id = 0;

	t = GET_THREAD(thread_base, thread_id, core_id, node_id, pkg_id);
	c = GET_CORE(core_base, core_id, node_id, pkg_id);
	p = GET_PKG(pkg_base, pkg_id);

	t->cpu_id = cpu_id;
	if (thread_id == 0) {
		t->flags |= CPU_IS_FIRST_THREAD_IN_CORE;
		if (cpu_is_first_core_in_package(cpu_id))
			t->flags |= CPU_IS_FIRST_CORE_IN_PACKAGE;
	}

	c->core_id = core_id;
	p->package_id = pkg_id;
}