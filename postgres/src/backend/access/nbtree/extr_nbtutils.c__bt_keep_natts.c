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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {TYPE_1__* scankeys; int /*<<< orphan*/  heapkeyspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_collation; int /*<<< orphan*/  sk_func; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__* BTScanInsert ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
_bt_keep_natts(Relation rel, IndexTuple lastleft, IndexTuple firstright,
			   BTScanInsert itup_key)
{
	int			nkeyatts = IndexRelationGetNumberOfKeyAttributes(rel);
	TupleDesc	itupdesc = RelationGetDescr(rel);
	int			keepnatts;
	ScanKey		scankey;

	/*
	 * Be consistent about the representation of BTREE_VERSION 2/3 tuples
	 * across Postgres versions; don't allow new pivot tuples to have
	 * truncated key attributes there.  _bt_compare() treats truncated key
	 * attributes as having the value minus infinity, which would break
	 * searches within !heapkeyspace indexes.
	 */
	if (!itup_key->heapkeyspace)
	{
		Assert(nkeyatts != IndexRelationGetNumberOfAttributes(rel));
		return nkeyatts;
	}

	scankey = itup_key->scankeys;
	keepnatts = 1;
	for (int attnum = 1; attnum <= nkeyatts; attnum++, scankey++)
	{
		Datum		datum1,
					datum2;
		bool		isNull1,
					isNull2;

		datum1 = index_getattr(lastleft, attnum, itupdesc, &isNull1);
		datum2 = index_getattr(firstright, attnum, itupdesc, &isNull2);

		if (isNull1 != isNull2)
			break;

		if (!isNull1 &&
			DatumGetInt32(FunctionCall2Coll(&scankey->sk_func,
											scankey->sk_collation,
											datum1,
											datum2)) != 0)
			break;

		keepnatts++;
	}

	return keepnatts;
}