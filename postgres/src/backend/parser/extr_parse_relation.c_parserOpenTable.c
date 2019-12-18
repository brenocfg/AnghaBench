#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  relname; scalar_t__ schemaname; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseCallbackState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  cancel_parser_errposition_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ isFutureCTE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_parser_errposition_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_openrv_extended (TYPE_1__ const*,int,int) ; 

Relation
parserOpenTable(ParseState *pstate, const RangeVar *relation, int lockmode)
{
	Relation	rel;
	ParseCallbackState pcbstate;

	setup_parser_errposition_callback(&pcbstate, pstate, relation->location);
	rel = table_openrv_extended(relation, lockmode, true);
	if (rel == NULL)
	{
		if (relation->schemaname)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_TABLE),
					 errmsg("relation \"%s.%s\" does not exist",
							relation->schemaname, relation->relname)));
		else
		{
			/*
			 * An unqualified name might have been meant as a reference to
			 * some not-yet-in-scope CTE.  The bare "does not exist" message
			 * has proven remarkably unhelpful for figuring out such problems,
			 * so we take pains to offer a specific hint.
			 */
			if (isFutureCTE(pstate, relation->relname))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_TABLE),
						 errmsg("relation \"%s\" does not exist",
								relation->relname),
						 errdetail("There is a WITH item named \"%s\", but it cannot be referenced from this part of the query.",
								   relation->relname),
						 errhint("Use WITH RECURSIVE, or re-order the WITH items to remove forward references.")));
			else
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_TABLE),
						 errmsg("relation \"%s\" does not exist",
								relation->relname)));
		}
	}
	cancel_parser_errposition_callback(&pcbstate);
	return rel;
}