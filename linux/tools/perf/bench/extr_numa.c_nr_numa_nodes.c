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
struct TYPE_3__ {int nr_nodes; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 TYPE_2__* g ; 
 scalar_t__ numa_bitmask_isbitset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numa_nodes_ptr ; 

__attribute__((used)) static int nr_numa_nodes(void)
{
	int i, nr_nodes = 0;

	for (i = 0; i < g->p.nr_nodes; i++) {
		if (numa_bitmask_isbitset(numa_nodes_ptr, i))
			nr_nodes++;
	}

	return nr_nodes;
}