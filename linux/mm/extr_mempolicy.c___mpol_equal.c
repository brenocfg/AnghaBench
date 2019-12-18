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
struct TYPE_4__ {int /*<<< orphan*/  preferred_node; int /*<<< orphan*/  nodes; } ;
struct TYPE_3__ {int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {int mode; scalar_t__ flags; TYPE_2__ v; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MPOL_BIND 130 
 int MPOL_F_LOCAL ; 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 scalar_t__ mpol_store_user_nodemask (struct mempolicy*) ; 
 int /*<<< orphan*/  nodes_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool __mpol_equal(struct mempolicy *a, struct mempolicy *b)
{
	if (!a || !b)
		return false;
	if (a->mode != b->mode)
		return false;
	if (a->flags != b->flags)
		return false;
	if (mpol_store_user_nodemask(a))
		if (!nodes_equal(a->w.user_nodemask, b->w.user_nodemask))
			return false;

	switch (a->mode) {
	case MPOL_BIND:
		/* Fall through */
	case MPOL_INTERLEAVE:
		return !!nodes_equal(a->v.nodes, b->v.nodes);
	case MPOL_PREFERRED:
		/* a's ->flags is the same as b's */
		if (a->flags & MPOL_F_LOCAL)
			return true;
		return a->v.preferred_node == b->v.preferred_node;
	default:
		BUG();
		return false;
	}
}