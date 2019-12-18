#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  indirection; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseExprKind ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ A_Indirection ;

/* Variables and functions */
 int /*<<< orphan*/ * ExpandRowReference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* copyObject (TYPE_1__*) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_truncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * transformExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
ExpandIndirectionStar(ParseState *pstate, A_Indirection *ind,
					  bool make_target_entry, ParseExprKind exprKind)
{
	Node	   *expr;

	/* Strip off the '*' to create a reference to the rowtype object */
	ind = copyObject(ind);
	ind->indirection = list_truncate(ind->indirection,
									 list_length(ind->indirection) - 1);

	/* And transform that */
	expr = transformExpr(pstate, (Node *) ind, exprKind);

	/* Expand the rowtype expression into individual fields */
	return ExpandRowReference(pstate, expr, make_target_entry);
}