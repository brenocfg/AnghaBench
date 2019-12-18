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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/ * t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTupleHeader ;
typedef  TYPE_1__ HeapTupleData ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Datum
GetAttributeByNum(HeapTupleHeader tuple,
				  AttrNumber attrno,
				  bool *isNull)
{
	Datum		result;
	Oid			tupType;
	int32		tupTypmod;
	TupleDesc	tupDesc;
	HeapTupleData tmptup;

	if (!AttributeNumberIsValid(attrno))
		elog(ERROR, "invalid attribute number %d", attrno);

	if (isNull == NULL)
		elog(ERROR, "a NULL isNull pointer was passed");

	if (tuple == NULL)
	{
		/* Kinda bogus but compatible with old behavior... */
		*isNull = true;
		return (Datum) 0;
	}

	tupType = HeapTupleHeaderGetTypeId(tuple);
	tupTypmod = HeapTupleHeaderGetTypMod(tuple);
	tupDesc = lookup_rowtype_tupdesc(tupType, tupTypmod);

	/*
	 * heap_getattr needs a HeapTuple not a bare HeapTupleHeader.  We set all
	 * the fields in the struct just in case user tries to inspect system
	 * columns.
	 */
	tmptup.t_len = HeapTupleHeaderGetDatumLength(tuple);
	ItemPointerSetInvalid(&(tmptup.t_self));
	tmptup.t_tableOid = InvalidOid;
	tmptup.t_data = tuple;

	result = heap_getattr(&tmptup,
						  attrno,
						  tupDesc,
						  isNull);

	ReleaseTupleDesc(tupDesc);

	return result;
}