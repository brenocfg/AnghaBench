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
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {scalar_t__ CurrBytePos; scalar_t__ PrevBytePos; int /*<<< orphan*/  insertpos_lck; } ;
typedef  TYPE_1__ XLogCtlInsert ;
struct TYPE_4__ {TYPE_1__ Insert; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int MAXALIGN (int) ; 
 int SizeOfXLogRecord ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogBytePosToEndRecPtr (scalar_t__) ; 
 int /*<<< orphan*/  XLogBytePosToRecPtr (scalar_t__) ; 
 TYPE_2__* XLogCtl ; 
 scalar_t__ XLogRecPtrToBytePos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ReserveXLogInsertLocation(int size, XLogRecPtr *StartPos, XLogRecPtr *EndPos,
						  XLogRecPtr *PrevPtr)
{
	XLogCtlInsert *Insert = &XLogCtl->Insert;
	uint64		startbytepos;
	uint64		endbytepos;
	uint64		prevbytepos;

	size = MAXALIGN(size);

	/* All (non xlog-switch) records should contain data. */
	Assert(size > SizeOfXLogRecord);

	/*
	 * The duration the spinlock needs to be held is minimized by minimizing
	 * the calculations that have to be done while holding the lock. The
	 * current tip of reserved WAL is kept in CurrBytePos, as a byte position
	 * that only counts "usable" bytes in WAL, that is, it excludes all WAL
	 * page headers. The mapping between "usable" byte positions and physical
	 * positions (XLogRecPtrs) can be done outside the locked region, and
	 * because the usable byte position doesn't include any headers, reserving
	 * X bytes from WAL is almost as simple as "CurrBytePos += X".
	 */
	SpinLockAcquire(&Insert->insertpos_lck);

	startbytepos = Insert->CurrBytePos;
	endbytepos = startbytepos + size;
	prevbytepos = Insert->PrevBytePos;
	Insert->CurrBytePos = endbytepos;
	Insert->PrevBytePos = startbytepos;

	SpinLockRelease(&Insert->insertpos_lck);

	*StartPos = XLogBytePosToRecPtr(startbytepos);
	*EndPos = XLogBytePosToEndRecPtr(endbytepos);
	*PrevPtr = XLogBytePosToRecPtr(prevbytepos);

	/*
	 * Check that the conversions between "usable byte positions" and
	 * XLogRecPtrs work consistently in both directions.
	 */
	Assert(XLogRecPtrToBytePos(*StartPos) == startbytepos);
	Assert(XLogRecPtrToBytePos(*EndPos) == endbytepos);
	Assert(XLogRecPtrToBytePos(*PrevPtr) == prevbytepos);
}