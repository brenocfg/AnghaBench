#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ parse; TYPE_1__* glob; } ;
struct TYPE_4__ {scalar_t__ lastPHId; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relids_in_jointree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  substitute_phv_relids (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_result_refs(PlannerInfo *root, int varno, Node *newjtloc)
{
	/* Fix up PlaceHolderVars as needed */
	/* If there are no PHVs anywhere, we can skip this bit */
	if (root->glob->lastPHId != 0)
	{
		Relids		subrelids;

		subrelids = get_relids_in_jointree(newjtloc, false);
		Assert(!bms_is_empty(subrelids));
		substitute_phv_relids((Node *) root->parse, varno, subrelids);
	}

	/*
	 * We also need to remove any PlanRowMark referencing the RTE, but we
	 * postpone that work until we return to remove_useless_result_rtes.
	 */
}