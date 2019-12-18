#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int t_infomask; } ;
typedef  TYPE_1__* HeapTupleHeader ;
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetRealCmin (int /*<<< orphan*/ ) ; 
 int HEAP_COMBOCID ; 
 int HEAP_MOVED ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawCommandId (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_1__*) ; 
 int TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 

CommandId
HeapTupleHeaderGetCmin(HeapTupleHeader tup)
{
	CommandId	cid = HeapTupleHeaderGetRawCommandId(tup);

	Assert(!(tup->t_infomask & HEAP_MOVED));
	Assert(TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetXmin(tup)));

	if (tup->t_infomask & HEAP_COMBOCID)
		return GetRealCmin(cid);
	else
		return cid;
}