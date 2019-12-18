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
struct TYPE_3__ {int /*<<< orphan*/  nodes; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpuset_mems_allowed; int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {int flags; TYPE_1__ v; TYPE_2__ w; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int MPOL_F_RELATIVE_NODES ; 
 int MPOL_F_STATIC_NODES ; 
 int /*<<< orphan*/  mpol_relative_nodemask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nodes_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ nodes_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_remap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void mpol_rebind_nodemask(struct mempolicy *pol, const nodemask_t *nodes)
{
	nodemask_t tmp;

	if (pol->flags & MPOL_F_STATIC_NODES)
		nodes_and(tmp, pol->w.user_nodemask, *nodes);
	else if (pol->flags & MPOL_F_RELATIVE_NODES)
		mpol_relative_nodemask(&tmp, &pol->w.user_nodemask, nodes);
	else {
		nodes_remap(tmp, pol->v.nodes,pol->w.cpuset_mems_allowed,
								*nodes);
		pol->w.cpuset_mems_allowed = *nodes;
	}

	if (nodes_empty(tmp))
		tmp = *nodes;

	pol->v.nodes = tmp;
}