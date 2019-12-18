#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_13__ {int heapkeyspace; int anynullkeys; int nextkey; int pivotsearch; int /*<<< orphan*/ * scankeys; int /*<<< orphan*/ * scantid; int /*<<< orphan*/  keysz; } ;
struct TYPE_12__ {int* rd_indoption; int /*<<< orphan*/ * rd_indcollation; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * ScanKey ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  scalar_t__ Datum ;
typedef  TYPE_2__* BTScanInsert ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTORDER_PROC ; 
 int /*<<< orphan*/  BTScanInsertData ; 
 int /*<<< orphan*/ * BTreeTupleGetHeapTID (int /*<<< orphan*/ *) ; 
 int BTreeTupleGetNAtts (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IndexRelationGetNumberOfAttributes (TYPE_1__*) ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvalidStrategy ; 
 int /*<<< orphan*/  Min (int,int) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_1__*) ; 
 int SK_BT_INDOPTION_SHIFT ; 
 int SK_ISNULL ; 
 int /*<<< orphan*/  ScanKeyEntryInitializeWithInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ _bt_heapkeyspace (TYPE_1__*) ; 
 scalar_t__ index_getattr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc (scalar_t__) ; 
 int /*<<< orphan*/  scankeys ; 

BTScanInsert
_bt_mkscankey(Relation rel, IndexTuple itup)
{
	BTScanInsert key;
	ScanKey		skey;
	TupleDesc	itupdesc;
	int			indnkeyatts;
	int16	   *indoption;
	int			tupnatts;
	int			i;

	itupdesc = RelationGetDescr(rel);
	indnkeyatts = IndexRelationGetNumberOfKeyAttributes(rel);
	indoption = rel->rd_indoption;
	tupnatts = itup ? BTreeTupleGetNAtts(itup, rel) : 0;

	Assert(tupnatts <= IndexRelationGetNumberOfAttributes(rel));

	/*
	 * We'll execute search using scan key constructed on key columns.
	 * Truncated attributes and non-key attributes are omitted from the final
	 * scan key.
	 */
	key = palloc(offsetof(BTScanInsertData, scankeys) +
				 sizeof(ScanKeyData) * indnkeyatts);
	key->heapkeyspace = itup == NULL || _bt_heapkeyspace(rel);
	key->anynullkeys = false;	/* initial assumption */
	key->nextkey = false;
	key->pivotsearch = false;
	key->keysz = Min(indnkeyatts, tupnatts);
	key->scantid = key->heapkeyspace && itup ?
		BTreeTupleGetHeapTID(itup) : NULL;
	skey = key->scankeys;
	for (i = 0; i < indnkeyatts; i++)
	{
		FmgrInfo   *procinfo;
		Datum		arg;
		bool		null;
		int			flags;

		/*
		 * We can use the cached (default) support procs since no cross-type
		 * comparison can be needed.
		 */
		procinfo = index_getprocinfo(rel, i + 1, BTORDER_PROC);

		/*
		 * Key arguments built from truncated attributes (or when caller
		 * provides no tuple) are defensively represented as NULL values. They
		 * should never be used.
		 */
		if (i < tupnatts)
			arg = index_getattr(itup, i + 1, itupdesc, &null);
		else
		{
			arg = (Datum) 0;
			null = true;
		}
		flags = (null ? SK_ISNULL : 0) | (indoption[i] << SK_BT_INDOPTION_SHIFT);
		ScanKeyEntryInitializeWithInfo(&skey[i],
									   flags,
									   (AttrNumber) (i + 1),
									   InvalidStrategy,
									   InvalidOid,
									   rel->rd_indcollation[i],
									   procinfo,
									   arg);
		/* Record if any key attribute is NULL (or truncated) */
		if (null)
			key->anynullkeys = true;
	}

	return key;
}