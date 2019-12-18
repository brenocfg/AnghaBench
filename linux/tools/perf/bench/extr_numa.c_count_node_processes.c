#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_data {int /*<<< orphan*/  curr_cpu; } ;
struct TYPE_3__ {int nr_proc; int nr_threads; } ;
struct TYPE_4__ {struct thread_data* threads; TYPE_1__ p; } ;

/* Variables and functions */
 TYPE_2__* g ; 
 int numa_node_of_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_node_processes(int node)
{
	int processes = 0;
	int t, p;

	for (p = 0; p < g->p.nr_proc; p++) {
		for (t = 0; t < g->p.nr_threads; t++) {
			struct thread_data *td;
			int task_nr;
			int n;

			task_nr = p*g->p.nr_threads + t;
			td = g->threads + task_nr;

			n = numa_node_of_cpu(td->curr_cpu);
			if (n == node) {
				processes++;
				break;
			}
		}
	}

	return processes;
}