#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ attisdropped; } ;
struct TYPE_3__ {int relnatts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int InvalidAttrNumber ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bms_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_del_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bms_is_member (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bitmapset *
fixup_whole_row_references(Oid relOid, Bitmapset *columns)
{
	Bitmapset  *result;
	HeapTuple	tuple;
	AttrNumber	natts;
	AttrNumber	attno;
	int			index;

	/* if no whole of row references, do not anything */
	index = InvalidAttrNumber - FirstLowInvalidHeapAttributeNumber;
	if (!bms_is_member(index, columns))
		return columns;

	/* obtain number of attributes */
	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relOid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", relOid);
	natts = ((Form_pg_class) GETSTRUCT(tuple))->relnatts;
	ReleaseSysCache(tuple);

	/* fix up the given columns */
	result = bms_copy(columns);
	result = bms_del_member(result, index);

	for (attno = 1; attno <= natts; attno++)
	{
		tuple = SearchSysCache2(ATTNUM,
								ObjectIdGetDatum(relOid),
								Int16GetDatum(attno));
		if (!HeapTupleIsValid(tuple))
			continue;

		if (((Form_pg_attribute) GETSTRUCT(tuple))->attisdropped)
			continue;

		index = attno - FirstLowInvalidHeapAttributeNumber;

		result = bms_add_member(result, index);

		ReleaseSysCache(tuple);
	}
	return result;
}