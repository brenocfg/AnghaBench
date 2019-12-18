#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int attisdropped; } ;
struct TYPE_4__ {int relnatts; scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_all_col_privileges(Oid table_oid, Form_pg_class classForm,
						  AclMode this_privileges,
						  AclMode *col_privileges,
						  int num_col_privileges)
{
	AttrNumber	curr_att;

	Assert(classForm->relnatts - FirstLowInvalidHeapAttributeNumber < num_col_privileges);
	for (curr_att = FirstLowInvalidHeapAttributeNumber + 1;
		 curr_att <= classForm->relnatts;
		 curr_att++)
	{
		HeapTuple	attTuple;
		bool		isdropped;

		if (curr_att == InvalidAttrNumber)
			continue;

		/* Views don't have any system columns at all */
		if (classForm->relkind == RELKIND_VIEW && curr_att < 0)
			continue;

		attTuple = SearchSysCache2(ATTNUM,
								   ObjectIdGetDatum(table_oid),
								   Int16GetDatum(curr_att));
		if (!HeapTupleIsValid(attTuple))
			elog(ERROR, "cache lookup failed for attribute %d of relation %u",
				 curr_att, table_oid);

		isdropped = ((Form_pg_attribute) GETSTRUCT(attTuple))->attisdropped;

		ReleaseSysCache(attTuple);

		/* ignore dropped columns */
		if (isdropped)
			continue;

		col_privileges[curr_att - FirstLowInvalidHeapAttributeNumber] |= this_privileges;
	}
}