#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ join_info_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  right_relids; int /*<<< orphan*/  left_relids; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_2__ PlannerInfo ;

/* Variables and functions */
 scalar_t__ NIL ; 
 int /*<<< orphan*/  bms_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ check_outerjoin_delay (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
check_equivalence_delay(PlannerInfo *root,
						RestrictInfo *restrictinfo)
{
	Relids		relids;
	Relids		nullable_relids;

	/* fast path if no special joins */
	if (root->join_info_list == NIL)
		return true;

	/* must copy restrictinfo's relids to avoid changing it */
	relids = bms_copy(restrictinfo->left_relids);
	/* check left side does not need delay */
	if (check_outerjoin_delay(root, &relids, &nullable_relids, true))
		return false;

	/* and similarly for the right side */
	relids = bms_copy(restrictinfo->right_relids);
	if (check_outerjoin_delay(root, &relids, &nullable_relids, true))
		return false;

	return true;
}