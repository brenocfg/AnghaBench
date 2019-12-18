#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* parse; TYPE_1__* glob; } ;
struct TYPE_7__ {int /*<<< orphan*/ * jointree; } ;
struct TYPE_6__ {scalar_t__ lastPHId; } ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FromExpr ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_placeholders_recurse (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
find_placeholders_in_jointree(PlannerInfo *root)
{
	/* We need do nothing if the query contains no PlaceHolderVars */
	if (root->glob->lastPHId != 0)
	{
		/* Start recursion at top of jointree */
		Assert(root->parse->jointree != NULL &&
			   IsA(root->parse->jointree, FromExpr));
		find_placeholders_recurse(root, (Node *) root->parse->jointree);
	}
}