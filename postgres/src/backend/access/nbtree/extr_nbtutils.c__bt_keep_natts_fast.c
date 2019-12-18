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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_1__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  datum_image_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

int
_bt_keep_natts_fast(Relation rel, IndexTuple lastleft, IndexTuple firstright)
{
	TupleDesc	itupdesc = RelationGetDescr(rel);
	int			keysz = IndexRelationGetNumberOfKeyAttributes(rel);
	int			keepnatts;

	keepnatts = 1;
	for (int attnum = 1; attnum <= keysz; attnum++)
	{
		Datum		datum1,
					datum2;
		bool		isNull1,
					isNull2;
		Form_pg_attribute att;

		datum1 = index_getattr(lastleft, attnum, itupdesc, &isNull1);
		datum2 = index_getattr(firstright, attnum, itupdesc, &isNull2);
		att = TupleDescAttr(itupdesc, attnum - 1);

		if (isNull1 != isNull2)
			break;

		if (!isNull1 &&
			!datum_image_eq(datum1, datum2, att->attbyval, att->attlen))
			break;

		keepnatts++;
	}

	return keepnatts;
}