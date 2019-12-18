#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {scalar_t__ CurrBytePos; scalar_t__ PrevBytePos; int /*<<< orphan*/  insertpos_lck; } ;
typedef  TYPE_1__ XLogCtlInsert ;
struct TYPE_4__ {TYPE_1__ Insert; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeOfXLogRecord ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogBytePosToEndRecPtr (scalar_t__) ; 
 int /*<<< orphan*/  XLogBytePosToRecPtr (scalar_t__) ; 
 TYPE_2__* XLogCtl ; 
 scalar_t__ XLogRecPtrToBytePos (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogSegmentOffset (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wal_segment_size ; 

__attribute__((used)) static bool
ReserveXLogSwitch(XLogRecPtr *StartPos, XLogRecPtr *EndPos, XLogRecPtr *PrevPtr)
{
	XLogCtlInsert *Insert = &XLogCtl->Insert;
	uint64		startbytepos;
	uint64		endbytepos;
	uint64		prevbytepos;
	uint32		size = MAXALIGN(SizeOfXLogRecord);
	XLogRecPtr	ptr;
	uint32		segleft;

	/*
	 * These calculations are a bit heavy-weight to be done while holding a
	 * spinlock, but since we're holding all the WAL insertion locks, there
	 * are no other inserters competing for it. GetXLogInsertRecPtr() does
	 * compete for it, but that's not called very frequently.
	 */
	SpinLockAcquire(&Insert->insertpos_lck);

	startbytepos = Insert->CurrBytePos;

	ptr = XLogBytePosToEndRecPtr(startbytepos);
	if (XLogSegmentOffset(ptr, wal_segment_size) == 0)
	{
		SpinLockRelease(&Insert->insertpos_lck);
		*EndPos = *StartPos = ptr;
		return false;
	}

	endbytepos = startbytepos + size;
	prevbytepos = Insert->PrevBytePos;

	*StartPos = XLogBytePosToRecPtr(startbytepos);
	*EndPos = XLogBytePosToEndRecPtr(endbytepos);

	segleft = wal_segment_size - XLogSegmentOffset(*EndPos, wal_segment_size);
	if (segleft != wal_segment_size)
	{
		/* consume the rest of the segment */
		*EndPos += segleft;
		endbytepos = XLogRecPtrToBytePos(*EndPos);
	}
	Insert->CurrBytePos = endbytepos;
	Insert->PrevBytePos = startbytepos;

	SpinLockRelease(&Insert->insertpos_lck);

	*PrevPtr = XLogBytePosToRecPtr(prevbytepos);

	Assert(XLogSegmentOffset(*EndPos, wal_segment_size) == 0);
	Assert(XLogRecPtrToBytePos(*EndPos) == endbytepos);
	Assert(XLogRecPtrToBytePos(*StartPos) == startbytepos);
	Assert(XLogRecPtrToBytePos(*PrevPtr) == prevbytepos);

	return true;
}