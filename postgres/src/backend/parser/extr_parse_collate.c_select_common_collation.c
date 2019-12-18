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
struct TYPE_3__ {scalar_t__ strength; int location; int /*<<< orphan*/  collation; int /*<<< orphan*/  location2; int /*<<< orphan*/ * pstate; int /*<<< orphan*/  collation2; } ;
typedef  TYPE_1__ assign_collations_context ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ COLLATE_CONFLICT ; 
 scalar_t__ COLLATE_NONE ; 
 int /*<<< orphan*/  ERRCODE_COLLATION_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  assign_collations_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_collation_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Oid
select_common_collation(ParseState *pstate, List *exprs, bool none_ok)
{
	assign_collations_context context;

	/* initialize context for tree walk */
	context.pstate = pstate;
	context.collation = InvalidOid;
	context.strength = COLLATE_NONE;
	context.location = -1;

	/* and away we go */
	(void) assign_collations_walker((Node *) exprs, &context);

	/* deal with collation conflict */
	if (context.strength == COLLATE_CONFLICT)
	{
		if (none_ok)
			return InvalidOid;
		ereport(ERROR,
				(errcode(ERRCODE_COLLATION_MISMATCH),
				 errmsg("collation mismatch between implicit collations \"%s\" and \"%s\"",
						get_collation_name(context.collation),
						get_collation_name(context.collation2)),
				 errhint("You can choose the collation by applying the COLLATE clause to one or both expressions."),
				 parser_errposition(context.pstate, context.location2)));
	}

	/*
	 * Note: if strength is still COLLATE_NONE, we'll return InvalidOid, but
	 * that's okay because it must mean none of the expressions returned
	 * collatable datatypes.
	 */
	return context.collation;
}