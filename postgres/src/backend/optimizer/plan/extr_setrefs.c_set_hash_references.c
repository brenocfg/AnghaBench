#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  indexed_tlist ;
struct TYPE_6__ {int /*<<< orphan*/ * hashkeys; } ;
struct TYPE_5__ {scalar_t__ qual; int /*<<< orphan*/  targetlist; struct TYPE_5__* lefttree; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Plan ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Hash ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  OUTER_VAR ; 
 int /*<<< orphan*/ * build_tlist_index (int /*<<< orphan*/ ) ; 
 scalar_t__ fix_upper_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dummy_tlist_references (TYPE_1__*,int) ; 

__attribute__((used)) static void
set_hash_references(PlannerInfo *root, Plan *plan, int rtoffset)
{
	Hash	   *hplan = (Hash *) plan;
	Plan	   *outer_plan = plan->lefttree;
	indexed_tlist *outer_itlist;

	/*
	 * Hash's hashkeys are used when feeding tuples into the hashtable,
	 * therefore have them reference Hash's outer plan (which itself is the
	 * inner plan of the HashJoin).
	 */
	outer_itlist = build_tlist_index(outer_plan->targetlist);
	hplan->hashkeys = (List *)
		fix_upper_expr(root,
					   (Node *) hplan->hashkeys,
					   outer_itlist,
					   OUTER_VAR,
					   rtoffset);

	/* Hash doesn't project */
	set_dummy_tlist_references(plan, rtoffset);

	/* Hash nodes don't have their own quals */
	Assert(plan->qual == NIL);
}