#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  indexed_tlist ;
struct TYPE_3__ {int /*<<< orphan*/  targetlist; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Plan ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/ * build_tlist_index_other_vars (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fix_join_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
set_returning_clause_references(PlannerInfo *root,
								List *rlist,
								Plan *topplan,
								Index resultRelation,
								int rtoffset)
{
	indexed_tlist *itlist;

	/*
	 * We can perform the desired Var fixup by abusing the fix_join_expr
	 * machinery that formerly handled inner indexscan fixup.  We search the
	 * top plan's targetlist for Vars of non-result relations, and use
	 * fix_join_expr to convert RETURNING Vars into references to those tlist
	 * entries, while leaving result-rel Vars as-is.
	 *
	 * PlaceHolderVars will also be sought in the targetlist, but no
	 * more-complex expressions will be.  Note that it is not possible for a
	 * PlaceHolderVar to refer to the result relation, since the result is
	 * never below an outer join.  If that case could happen, we'd have to be
	 * prepared to pick apart the PlaceHolderVar and evaluate its contained
	 * expression instead.
	 */
	itlist = build_tlist_index_other_vars(topplan->targetlist, resultRelation);

	rlist = fix_join_expr(root,
						  rlist,
						  itlist,
						  NULL,
						  resultRelation,
						  rtoffset);

	pfree(itlist);

	return rlist;
}