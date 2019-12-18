#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_12__ {scalar_t__ attnum; int /*<<< orphan*/  attname; } ;
struct TYPE_11__ {int /*<<< orphan*/ * t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
struct TYPE_10__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTupleHeader ;
typedef  TYPE_2__ HeapTupleData ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_1__*) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_2__*,scalar_t__,TYPE_1__*,int*) ; 
 TYPE_1__* lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 

Datum
GetAttributeByName(HeapTupleHeader tuple, const char *attname, bool *isNull)
{
	AttrNumber	attrno;
	Datum		result;
	Oid			tupType;
	int32		tupTypmod;
	TupleDesc	tupDesc;
	HeapTupleData tmptup;
	int			i;

	if (attname == NULL)
		elog(ERROR, "invalid attribute name");

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

	attrno = InvalidAttrNumber;
	for (i = 0; i < tupDesc->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupDesc, i);

		if (namestrcmp(&(att->attname), attname) == 0)
		{
			attrno = att->attnum;
			break;
		}
	}

	if (attrno == InvalidAttrNumber)
		elog(ERROR, "attribute \"%s\" does not exist", attname);

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