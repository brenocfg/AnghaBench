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
struct TYPE_2__ {int nredirected; int ndead; int /*<<< orphan*/  latestRemovedXid; } ;
typedef  TYPE_1__ xl_heap_clean ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 int /*<<< orphan*/  RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeOfHeapClean ; 
 int /*<<< orphan*/  XLOG_HEAP2_CLEAN ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

XLogRecPtr
log_heap_clean(Relation reln, Buffer buffer,
			   OffsetNumber *redirected, int nredirected,
			   OffsetNumber *nowdead, int ndead,
			   OffsetNumber *nowunused, int nunused,
			   TransactionId latestRemovedXid)
{
	xl_heap_clean xlrec;
	XLogRecPtr	recptr;

	/* Caller should not call me on a non-WAL-logged relation */
	Assert(RelationNeedsWAL(reln));

	xlrec.latestRemovedXid = latestRemovedXid;
	xlrec.nredirected = nredirected;
	xlrec.ndead = ndead;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, SizeOfHeapClean);

	XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

	/*
	 * The OffsetNumber arrays are not actually in the buffer, but we pretend
	 * that they are.  When XLogInsert stores the whole buffer, the offset
	 * arrays need not be stored too.  Note that even if all three arrays are
	 * empty, we want to expose the buffer as a candidate for whole-page
	 * storage, since this record type implies a defragmentation operation
	 * even if no line pointers changed state.
	 */
	if (nredirected > 0)
		XLogRegisterBufData(0, (char *) redirected,
							nredirected * sizeof(OffsetNumber) * 2);

	if (ndead > 0)
		XLogRegisterBufData(0, (char *) nowdead,
							ndead * sizeof(OffsetNumber));

	if (nunused > 0)
		XLogRegisterBufData(0, (char *) nowunused,
							nunused * sizeof(OffsetNumber));

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_CLEAN);

	return recptr;
}