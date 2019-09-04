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
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {TYPE_1__ v; } ;

/* Variables and functions */
 int first_node (int /*<<< orphan*/ ) ; 
 int next_node (int,int /*<<< orphan*/ ) ; 
 unsigned int nodes_weight (int /*<<< orphan*/ ) ; 
 int numa_node_id () ; 

__attribute__((used)) static unsigned offset_il_node(struct mempolicy *pol, unsigned long n)
{
	unsigned nnodes = nodes_weight(pol->v.nodes);
	unsigned target;
	int i;
	int nid;

	if (!nnodes)
		return numa_node_id();
	target = (unsigned int)n % nnodes;
	nid = first_node(pol->v.nodes);
	for (i = 0; i < target; i++)
		nid = next_node(nid, pol->v.nodes);
	return nid;
}