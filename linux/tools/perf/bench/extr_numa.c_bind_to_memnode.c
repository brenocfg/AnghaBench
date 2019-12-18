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
typedef  int /*<<< orphan*/  nodemask ;
struct TYPE_3__ {int nr_nodes; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MPOL_BIND ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  dprintf (char*,int,unsigned long,int) ; 
 TYPE_2__* g ; 
 int set_mempolicy (int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static void bind_to_memnode(int node)
{
	unsigned long nodemask;
	int ret;

	if (node == NUMA_NO_NODE)
		return;

	BUG_ON(g->p.nr_nodes > (int)sizeof(nodemask)*8);
	nodemask = 1L << node;

	ret = set_mempolicy(MPOL_BIND, &nodemask, sizeof(nodemask)*8);
	dprintf("binding to node %d, mask: %016lx => %d\n", node, nodemask, ret);

	BUG_ON(ret);
}