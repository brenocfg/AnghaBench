#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ paramkind; int paramid; } ;
struct TYPE_7__ {int /*<<< orphan*/ * multiexpr_params; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  TYPE_2__ Param ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PARAM_MULTIEXPR ; 
 int /*<<< orphan*/ * copyObject (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_nth (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Node *
fix_param_node(PlannerInfo *root, Param *p)
{
	if (p->paramkind == PARAM_MULTIEXPR)
	{
		int			subqueryid = p->paramid >> 16;
		int			colno = p->paramid & 0xFFFF;
		List	   *params;

		if (subqueryid <= 0 ||
			subqueryid > list_length(root->multiexpr_params))
			elog(ERROR, "unexpected PARAM_MULTIEXPR ID: %d", p->paramid);
		params = (List *) list_nth(root->multiexpr_params, subqueryid - 1);
		if (colno <= 0 || colno > list_length(params))
			elog(ERROR, "unexpected PARAM_MULTIEXPR ID: %d", p->paramid);
		return copyObject(list_nth(params, colno - 1));
	}
	return (Node *) copyObject(p);
}