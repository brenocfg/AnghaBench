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
struct cpuset {int /*<<< orphan*/  effective_mems; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 size_t N_MEMORY ; 
 int /*<<< orphan*/ * node_states ; 
 int /*<<< orphan*/  nodes_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 

__attribute__((used)) static void guarantee_online_mems(struct cpuset *cs, nodemask_t *pmask)
{
	while (!nodes_intersects(cs->effective_mems, node_states[N_MEMORY]))
		cs = parent_cs(cs);
	nodes_and(*pmask, cs->effective_mems, node_states[N_MEMORY]);
}