#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* combocid; void* cmax; void* cmin; int /*<<< orphan*/  target_tid; int /*<<< orphan*/  target_node; int /*<<< orphan*/  top_xid; } ;
typedef  TYPE_1__ xl_heap_new_cid ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_14__ {scalar_t__ t_tableOid; int /*<<< orphan*/  t_self; TYPE_3__* t_data; } ;
struct TYPE_13__ {int t_infomask; } ;
struct TYPE_12__ {int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* HeapTupleHeader ;
typedef  TYPE_4__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetTopTransactionId () ; 
 int HEAP_COMBOCID ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 void* HeapTupleHeaderGetCmax (TYPE_3__*) ; 
 void* HeapTupleHeaderGetCmin (TYPE_3__*) ; 
 void* HeapTupleHeaderGetRawCommandId (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminInvalid (TYPE_3__*) ; 
 void* InvalidCommandId ; 
 scalar_t__ InvalidOid ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 int /*<<< orphan*/  SizeOfHeapNewCid ; 
 int /*<<< orphan*/  XLOG_HEAP2_NEW_CID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static XLogRecPtr
log_heap_new_cid(Relation relation, HeapTuple tup)
{
	xl_heap_new_cid xlrec;

	XLogRecPtr	recptr;
	HeapTupleHeader hdr = tup->t_data;

	Assert(ItemPointerIsValid(&tup->t_self));
	Assert(tup->t_tableOid != InvalidOid);

	xlrec.top_xid = GetTopTransactionId();
	xlrec.target_node = relation->rd_node;
	xlrec.target_tid = tup->t_self;

	/*
	 * If the tuple got inserted & deleted in the same TX we definitely have a
	 * combocid, set cmin and cmax.
	 */
	if (hdr->t_infomask & HEAP_COMBOCID)
	{
		Assert(!(hdr->t_infomask & HEAP_XMAX_INVALID));
		Assert(!HeapTupleHeaderXminInvalid(hdr));
		xlrec.cmin = HeapTupleHeaderGetCmin(hdr);
		xlrec.cmax = HeapTupleHeaderGetCmax(hdr);
		xlrec.combocid = HeapTupleHeaderGetRawCommandId(hdr);
	}
	/* No combocid, so only cmin or cmax can be set by this TX */
	else
	{
		/*
		 * Tuple inserted.
		 *
		 * We need to check for LOCK ONLY because multixacts might be
		 * transferred to the new tuple in case of FOR KEY SHARE updates in
		 * which case there will be an xmax, although the tuple just got
		 * inserted.
		 */
		if (hdr->t_infomask & HEAP_XMAX_INVALID ||
			HEAP_XMAX_IS_LOCKED_ONLY(hdr->t_infomask))
		{
			xlrec.cmin = HeapTupleHeaderGetRawCommandId(hdr);
			xlrec.cmax = InvalidCommandId;
		}
		/* Tuple from a different tx updated or deleted. */
		else
		{
			xlrec.cmin = InvalidCommandId;
			xlrec.cmax = HeapTupleHeaderGetRawCommandId(hdr);

		}
		xlrec.combocid = InvalidCommandId;
	}

	/*
	 * Note that we don't need to register the buffer here, because this
	 * operation does not modify the page. The insert/update/delete that
	 * called us certainly did, but that's WAL-logged separately.
	 */
	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, SizeOfHeapNewCid);

	/* will be looked at irrespective of origin */

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_NEW_CID);

	return recptr;
}