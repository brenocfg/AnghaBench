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
struct TYPE_2__ {int /*<<< orphan*/  preferred_node; } ;
struct mempolicy {TYPE_1__ v; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPOL_F_LOCAL ; 
 int /*<<< orphan*/  first_node (int /*<<< orphan*/  const) ; 
 scalar_t__ nodes_empty (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int mpol_new_preferred(struct mempolicy *pol, const nodemask_t *nodes)
{
	if (!nodes)
		pol->flags |= MPOL_F_LOCAL;	/* local allocation */
	else if (nodes_empty(*nodes))
		return -EINVAL;			/*  no allowed nodes */
	else
		pol->v.preferred_node = first_node(*nodes);
	return 0;
}