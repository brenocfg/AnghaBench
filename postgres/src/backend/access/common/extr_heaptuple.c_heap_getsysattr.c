#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_self; } ;
typedef  TYPE_1__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (TYPE_1__*) ; 
 int /*<<< orphan*/  CommandIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawCommandId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmin (int /*<<< orphan*/ ) ; 
#define  MaxCommandIdAttributeNumber 133 
#define  MaxTransactionIdAttributeNumber 132 
#define  MinCommandIdAttributeNumber 131 
#define  MinTransactionIdAttributeNumber 130 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
#define  SelfItemPointerAttributeNumber 129 
#define  TableOidAttributeNumber 128 
 int /*<<< orphan*/  TransactionIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

Datum
heap_getsysattr(HeapTuple tup, int attnum, TupleDesc tupleDesc, bool *isnull)
{
	Datum		result;

	Assert(tup);

	/* Currently, no sys attribute ever reads as NULL. */
	*isnull = false;

	switch (attnum)
	{
		case SelfItemPointerAttributeNumber:
			/* pass-by-reference datatype */
			result = PointerGetDatum(&(tup->t_self));
			break;
		case MinTransactionIdAttributeNumber:
			result = TransactionIdGetDatum(HeapTupleHeaderGetRawXmin(tup->t_data));
			break;
		case MaxTransactionIdAttributeNumber:
			result = TransactionIdGetDatum(HeapTupleHeaderGetRawXmax(tup->t_data));
			break;
		case MinCommandIdAttributeNumber:
		case MaxCommandIdAttributeNumber:

			/*
			 * cmin and cmax are now both aliases for the same field, which
			 * can in fact also be a combo command id.  XXX perhaps we should
			 * return the "real" cmin or cmax if possible, that is if we are
			 * inside the originating transaction?
			 */
			result = CommandIdGetDatum(HeapTupleHeaderGetRawCommandId(tup->t_data));
			break;
		case TableOidAttributeNumber:
			result = ObjectIdGetDatum(tup->t_tableOid);
			break;
		default:
			elog(ERROR, "invalid attnum: %d", attnum);
			result = 0;			/* keep compiler quiet */
			break;
	}
	return result;
}