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
struct TYPE_3__ {scalar_t__ expr; } ;
typedef  TYPE_1__ TargetEntry ;
typedef  int /*<<< orphan*/  SortGroupClause ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 TYPE_1__* get_sortgroupclause_tle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Node *
get_sortgroupclause_expr(SortGroupClause *sgClause, List *targetList)
{
	TargetEntry *tle = get_sortgroupclause_tle(sgClause, targetList);

	return (Node *) tle->expr;
}