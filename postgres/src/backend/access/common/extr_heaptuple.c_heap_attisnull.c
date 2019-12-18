#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_12__ {int /*<<< orphan*/  t_bits; } ;
struct TYPE_11__ {scalar_t__ atthasmissing; } ;
struct TYPE_10__ {TYPE_8__* t_data; } ;
struct TYPE_9__ {int natts; } ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HeapTupleHeaderGetNatts (TYPE_8__*) ; 
 scalar_t__ HeapTupleNoNulls (TYPE_2__*) ; 
#define  MaxCommandIdAttributeNumber 133 
#define  MaxTransactionIdAttributeNumber 132 
#define  MinCommandIdAttributeNumber 131 
#define  MinTransactionIdAttributeNumber 130 
#define  SelfItemPointerAttributeNumber 129 
#define  TableOidAttributeNumber 128 
 TYPE_5__* TupleDescAttr (TYPE_1__*,int) ; 
 int att_isnull (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

bool
heap_attisnull(HeapTuple tup, int attnum, TupleDesc tupleDesc)
{
	/*
	 * We allow a NULL tupledesc for relations not expected to have missing
	 * values, such as catalog relations and indexes.
	 */
	Assert(!tupleDesc || attnum <= tupleDesc->natts);
	if (attnum > (int) HeapTupleHeaderGetNatts(tup->t_data))
	{
		if (tupleDesc && TupleDescAttr(tupleDesc, attnum - 1)->atthasmissing)
			return false;
		else
			return true;
	}

	if (attnum > 0)
	{
		if (HeapTupleNoNulls(tup))
			return false;
		return att_isnull(attnum - 1, tup->t_data->t_bits);
	}

	switch (attnum)
	{
		case TableOidAttributeNumber:
		case SelfItemPointerAttributeNumber:
		case MinTransactionIdAttributeNumber:
		case MinCommandIdAttributeNumber:
		case MaxTransactionIdAttributeNumber:
		case MaxCommandIdAttributeNumber:
			/* these are never null */
			break;

		default:
			elog(ERROR, "invalid attnum: %d", attnum);
	}

	return false;
}