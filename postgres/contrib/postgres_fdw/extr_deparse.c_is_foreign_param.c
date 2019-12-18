#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  varlevelsup; int /*<<< orphan*/  varno; } ;
typedef  TYPE_2__ Var ;
struct TYPE_10__ {TYPE_1__* outerrel; } ;
struct TYPE_9__ {int /*<<< orphan*/  relids; scalar_t__ fdw_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  relids; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_3__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_4__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UPPER_REL (TYPE_3__*) ; 
#define  T_Param 129 
#define  T_Var 128 
 int /*<<< orphan*/  bms_is_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

bool
is_foreign_param(PlannerInfo *root,
				 RelOptInfo *baserel,
				 Expr *expr)
{
	if (expr == NULL)
		return false;

	switch (nodeTag(expr))
	{
		case T_Var:
			{
				/* It would have to be sent unless it's a foreign Var */
				Var		   *var = (Var *) expr;
				PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) (baserel->fdw_private);
				Relids		relids;

				if (IS_UPPER_REL(baserel))
					relids = fpinfo->outerrel->relids;
				else
					relids = baserel->relids;

				if (bms_is_member(var->varno, relids) && var->varlevelsup == 0)
					return false;	/* foreign Var, so not a param */
				else
					return true;	/* it'd have to be a param */
				break;
			}
		case T_Param:
			/* Params always have to be sent to the foreign server */
			return true;
		default:
			break;
	}
	return false;
}