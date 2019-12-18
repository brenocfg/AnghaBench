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
struct inline_cte_walker_context {int levelsup; scalar_t__ refcount; int /*<<< orphan*/  ctequery; int /*<<< orphan*/  ctename; } ;
struct TYPE_6__ {scalar_t__ cterefcount; int /*<<< orphan*/  ctequery; int /*<<< orphan*/  ctename; } ;
struct TYPE_5__ {scalar_t__ parse; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ CommonTableExpr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  Query ; 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inline_cte_walker (int /*<<< orphan*/ *,struct inline_cte_walker_context*) ; 

__attribute__((used)) static void
inline_cte(PlannerInfo *root, CommonTableExpr *cte)
{
	struct inline_cte_walker_context context;

	context.ctename = cte->ctename;
	/* Start at levelsup = -1 because we'll immediately increment it */
	context.levelsup = -1;
	context.refcount = cte->cterefcount;
	context.ctequery = castNode(Query, cte->ctequery);

	(void) inline_cte_walker((Node *) root->parse, &context);

	/* Assert we replaced all references */
	Assert(context.refcount == 0);
}