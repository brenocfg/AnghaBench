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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cutoff_xid; } ;
typedef  TYPE_1__ xl_heap_visible ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_NO_IMAGE ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 int /*<<< orphan*/  SizeOfHeapVisible ; 
 int /*<<< orphan*/  XLOG_HEAP2_VISIBLE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogHintBitIsNeeded () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

XLogRecPtr
log_heap_visible(RelFileNode rnode, Buffer heap_buffer, Buffer vm_buffer,
				 TransactionId cutoff_xid, uint8 vmflags)
{
	xl_heap_visible xlrec;
	XLogRecPtr	recptr;
	uint8		flags;

	Assert(BufferIsValid(heap_buffer));
	Assert(BufferIsValid(vm_buffer));

	xlrec.cutoff_xid = cutoff_xid;
	xlrec.flags = vmflags;
	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, SizeOfHeapVisible);

	XLogRegisterBuffer(0, vm_buffer, 0);

	flags = REGBUF_STANDARD;
	if (!XLogHintBitIsNeeded())
		flags |= REGBUF_NO_IMAGE;
	XLogRegisterBuffer(1, heap_buffer, flags);

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_VISIBLE);

	return recptr;
}