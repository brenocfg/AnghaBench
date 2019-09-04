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
struct TYPE_3__ {int nr_proc; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 unsigned int count_process_nodes (int) ; 
 TYPE_2__* g ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tprintf (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void calc_convergence_compression(int *strong)
{
	unsigned int nodes_min, nodes_max;
	int p;

	nodes_min = -1;
	nodes_max =  0;

	for (p = 0; p < g->p.nr_proc; p++) {
		unsigned int nodes = count_process_nodes(p);

		if (!nodes) {
			*strong = 0;
			return;
		}

		nodes_min = min(nodes, nodes_min);
		nodes_max = max(nodes, nodes_max);
	}

	/* Strong convergence: all threads compress on a single node: */
	if (nodes_min == 1 && nodes_max == 1) {
		*strong = 1;
	} else {
		*strong = 0;
		tprintf(" {%d-%d}", nodes_min, nodes_max);
	}
}