#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_10__ {scalar_t__ atttypid; } ;
struct TYPE_9__ {int /*<<< orphan*/  flinfo; } ;
struct TYPE_8__ {int natts; } ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  TYPE_3__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INT4OID ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_fn_expr_argtype (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hypothetical_check_argtypes(FunctionCallInfo fcinfo, int nargs,
							TupleDesc tupdesc)
{
	int			i;

	/* check that we have an int4 flag column */
	if (!tupdesc ||
		(nargs + 1) != tupdesc->natts ||
		TupleDescAttr(tupdesc, nargs)->atttypid != INT4OID)
		elog(ERROR, "type mismatch in hypothetical-set function");

	/* check that direct args match in type with aggregated args */
	for (i = 0; i < nargs; i++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

		if (get_fn_expr_argtype(fcinfo->flinfo, i + 1) != attr->atttypid)
			elog(ERROR, "type mismatch in hypothetical-set function");
	}
}