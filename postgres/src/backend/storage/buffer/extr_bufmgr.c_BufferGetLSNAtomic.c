#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  BufferDesc ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* BufferGetPage (scalar_t__) ; 
 scalar_t__ BufferIsLocal (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsPinned (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/ * GetBufferDescriptor (scalar_t__) ; 
 int /*<<< orphan*/  LockBufHdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageGetLSN (char*) ; 
 int /*<<< orphan*/  UnlockBufHdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogHintBitIsNeeded () ; 

XLogRecPtr
BufferGetLSNAtomic(Buffer buffer)
{
	BufferDesc *bufHdr = GetBufferDescriptor(buffer - 1);
	char	   *page = BufferGetPage(buffer);
	XLogRecPtr	lsn;
	uint32		buf_state;

	/*
	 * If we don't need locking for correctness, fastpath out.
	 */
	if (!XLogHintBitIsNeeded() || BufferIsLocal(buffer))
		return PageGetLSN(page);

	/* Make sure we've got a real buffer, and that we hold a pin on it. */
	Assert(BufferIsValid(buffer));
	Assert(BufferIsPinned(buffer));

	buf_state = LockBufHdr(bufHdr);
	lsn = PageGetLSN(page);
	UnlockBufHdr(bufHdr, buf_state);

	return lsn;
}