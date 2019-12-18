#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  params_list; int /*<<< orphan*/  root; int /*<<< orphan*/  foreignrel; TYPE_2__* scanrel; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_expr_cxt ;
struct TYPE_9__ {int /*<<< orphan*/  relids; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BMS_MULTIPLE ; 
 scalar_t__ IS_JOIN_REL (TYPE_2__*) ; 
 scalar_t__ IS_SIMPLE_REL (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_UPPER_REL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  appendConditions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bms_membership (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparseFromExprForRel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deparseFromExpr(List *quals, deparse_expr_cxt *context)
{
	StringInfo	buf = context->buf;
	RelOptInfo *scanrel = context->scanrel;

	/* For upper relations, scanrel must be either a joinrel or a baserel */
	Assert(!IS_UPPER_REL(context->foreignrel) ||
		   IS_JOIN_REL(scanrel) || IS_SIMPLE_REL(scanrel));

	/* Construct FROM clause */
	appendStringInfoString(buf, " FROM ");
	deparseFromExprForRel(buf, context->root, scanrel,
						  (bms_membership(scanrel->relids) == BMS_MULTIPLE),
						  (Index) 0, NULL, context->params_list);

	/* Construct WHERE clause */
	if (quals != NIL)
	{
		appendStringInfoString(buf, " WHERE ");
		appendConditions(quals, context);
	}
}