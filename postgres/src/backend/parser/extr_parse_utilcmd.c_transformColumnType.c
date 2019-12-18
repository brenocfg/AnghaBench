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
typedef  int /*<<< orphan*/  Type ;
struct TYPE_10__ {TYPE_1__* collClause; int /*<<< orphan*/  typeName; } ;
struct TYPE_9__ {int /*<<< orphan*/  pstate; } ;
struct TYPE_8__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  typcollation; } ;
struct TYPE_7__ {int /*<<< orphan*/  location; int /*<<< orphan*/  collname; } ;
typedef  TYPE_2__* Form_pg_type ;
typedef  TYPE_3__ CreateStmtContext ;
typedef  TYPE_4__ ColumnDef ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupCollation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typenameType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
transformColumnType(CreateStmtContext *cxt, ColumnDef *column)
{
	/*
	 * All we really need to do here is verify that the type is valid,
	 * including any collation spec that might be present.
	 */
	Type		ctype = typenameType(cxt->pstate, column->typeName, NULL);

	if (column->collClause)
	{
		Form_pg_type typtup = (Form_pg_type) GETSTRUCT(ctype);

		LookupCollation(cxt->pstate,
						column->collClause->collname,
						column->collClause->location);
		/* Complain if COLLATE is applied to an uncollatable type */
		if (!OidIsValid(typtup->typcollation))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("collations are not supported by type %s",
							format_type_be(typtup->oid)),
					 parser_errposition(cxt->pstate,
										column->collClause->location)));
	}

	ReleaseSysCache(ctype);
}