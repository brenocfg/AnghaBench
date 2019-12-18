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
struct thread_data {int /*<<< orphan*/  cpu_id; } ;
struct pkg_data {int dummy; } ;
struct core_data {int dummy; } ;
struct TYPE_2__ {int num_packages; int nodes_per_pkg; int cores_per_node; int threads_per_core; } ;

/* Variables and functions */
 struct core_data* GET_CORE (struct core_data*,int,int,int) ; 
 struct pkg_data* GET_PKG (struct pkg_data*,int) ; 
 struct thread_data* GET_THREAD (struct thread_data*,int,int,int,int) ; 
 scalar_t__ cpu_is_not_present (int /*<<< orphan*/ ) ; 
 TYPE_1__ topo ; 

int for_all_cpus(int (func)(struct thread_data *, struct core_data *, struct pkg_data *),
	struct thread_data *thread_base, struct core_data *core_base, struct pkg_data *pkg_base)
{
	int retval, pkg_no, core_no, thread_no, node_no;

	for (pkg_no = 0; pkg_no < topo.num_packages; ++pkg_no) {
		for (node_no = 0; node_no < topo.nodes_per_pkg; node_no++) {
			for (core_no = 0; core_no < topo.cores_per_node; ++core_no) {
				for (thread_no = 0; thread_no <
					topo.threads_per_core; ++thread_no) {
					struct thread_data *t;
					struct core_data *c;
					struct pkg_data *p;

					t = GET_THREAD(thread_base, thread_no,
						       core_no, node_no,
						       pkg_no);

					if (cpu_is_not_present(t->cpu_id))
						continue;

					c = GET_CORE(core_base, core_no,
						     node_no, pkg_no);
					p = GET_PKG(pkg_base, pkg_no);

					retval = func(t, c, p);
					if (retval)
						return retval;
				}
			}
		}
	}
	return 0;
}