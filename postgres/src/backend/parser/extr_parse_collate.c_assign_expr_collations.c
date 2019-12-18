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
struct TYPE_3__ {int location; int /*<<< orphan*/  strength; int /*<<< orphan*/  collation; int /*<<< orphan*/ * pstate; } ;
typedef  TYPE_1__ assign_collations_context ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  COLLATE_NONE ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  assign_collations_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
assign_expr_collations(ParseState *pstate, Node *expr)
{
	assign_collations_context context;

	/* initialize context for tree walk */
	context.pstate = pstate;
	context.collation = InvalidOid;
	context.strength = COLLATE_NONE;
	context.location = -1;

	/* and away we go */
	(void) assign_collations_walker(expr, &context);
}