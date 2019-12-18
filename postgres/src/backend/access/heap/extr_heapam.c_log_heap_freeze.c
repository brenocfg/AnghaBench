#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xl_heap_freeze_tuple ;
struct TYPE_2__ {int ntuples; int /*<<< orphan*/  cutoff_xid; } ;
typedef  TYPE_1__ xl_heap_freeze_page ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 int RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeOfHeapFreezePage ; 
 int /*<<< orphan*/  XLOG_HEAP2_FREEZE_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

XLogRecPtr
log_heap_freeze(Relation reln, Buffer buffer, TransactionId cutoff_xid,
				xl_heap_freeze_tuple *tuples, int ntuples)
{
	xl_heap_freeze_page xlrec;
	XLogRecPtr	recptr;

	/* Caller should not call me on a non-WAL-logged relation */
	Assert(RelationNeedsWAL(reln));
	/* nor when there are no tuples to freeze */
	Assert(ntuples > 0);

	xlrec.cutoff_xid = cutoff_xid;
	xlrec.ntuples = ntuples;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, SizeOfHeapFreezePage);

	/*
	 * The freeze plan array is not actually in the buffer, but pretend that
	 * it is.  When XLogInsert stores the whole buffer, the freeze plan need
	 * not be stored too.
	 */
	XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);
	XLogRegisterBufData(0, (char *) tuples,
						ntuples * sizeof(xl_heap_freeze_tuple));

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_FREEZE_PAGE);

	return recptr;
}