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
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  GetRealCmax (int /*<<< orphan*/ ) ; 
 int HEAP_COMBOCID ; 
 int HEAP_MOVED ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawCommandId (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_1__*) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 

CommandId
HeapTupleHeaderGetCmax(HeapTupleHeader tup)
{
	CommandId	cid = HeapTupleHeaderGetRawCommandId(tup);

	Assert(!(tup->t_infomask & HEAP_MOVED));

	/*
	 * Because GetUpdateXid() performs memory allocations if xmax is a
	 * multixact we can't Assert() if we're inside a critical section. This
	 * weakens the check, but not using GetCmax() inside one would complicate
	 * things too much.
	 */
	Assert(CritSectionCount > 0 ||
		   TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetUpdateXid(tup)));

	if (tup->t_infomask & HEAP_COMBOCID)
		return GetRealCmax(cid);
	else
		return cid;
}