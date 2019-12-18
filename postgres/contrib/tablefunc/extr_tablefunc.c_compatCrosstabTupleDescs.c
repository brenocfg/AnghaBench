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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {scalar_t__ atttypid; } ;
struct TYPE_7__ {int natts; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static bool
compatCrosstabTupleDescs(TupleDesc ret_tupdesc, TupleDesc sql_tupdesc)
{
	int			i;
	Form_pg_attribute ret_attr;
	Oid			ret_atttypid;
	Form_pg_attribute sql_attr;
	Oid			sql_atttypid;

	if (ret_tupdesc->natts < 2 ||
		sql_tupdesc->natts < 3)
		return false;

	/* check the rowid types match */
	ret_atttypid = TupleDescAttr(ret_tupdesc, 0)->atttypid;
	sql_atttypid = TupleDescAttr(sql_tupdesc, 0)->atttypid;
	if (ret_atttypid != sql_atttypid)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("invalid return type"),
				 errdetail("SQL rowid datatype does not match " \
						   "return rowid datatype.")));

	/*
	 * - attribute [1] of the sql tuple is the category; no need to check it -
	 * attribute [2] of the sql tuple should match attributes [1] to [natts]
	 * of the return tuple
	 */
	sql_attr = TupleDescAttr(sql_tupdesc, 2);
	for (i = 1; i < ret_tupdesc->natts; i++)
	{
		ret_attr = TupleDescAttr(ret_tupdesc, i);

		if (ret_attr->atttypid != sql_attr->atttypid)
			return false;
	}

	/* OK, the two tupdescs are compatible for our purposes */
	return true;
}