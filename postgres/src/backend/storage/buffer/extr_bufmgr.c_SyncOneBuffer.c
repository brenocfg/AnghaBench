#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  WritebackContext ;
struct TYPE_9__ {int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int BM_DIRTY ; 
 int BM_VALID ; 
 int BUF_REUSABLE ; 
 scalar_t__ BUF_STATE_GET_REFCOUNT (int) ; 
 scalar_t__ BUF_STATE_GET_USAGECOUNT (int) ; 
 int BUF_WRITTEN ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_1__*) ; 
 int /*<<< orphan*/  FlushBuffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* GetBufferDescriptor (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int LockBufHdr (TYPE_1__*) ; 
 int /*<<< orphan*/  PinBuffer_Locked (TYPE_1__*) ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 int /*<<< orphan*/  ScheduleBufferTagForWriteback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UnpinBuffer (TYPE_1__*,int) ; 

__attribute__((used)) static int
SyncOneBuffer(int buf_id, bool skip_recently_used, WritebackContext *wb_context)
{
	BufferDesc *bufHdr = GetBufferDescriptor(buf_id);
	int			result = 0;
	uint32		buf_state;
	BufferTag	tag;

	ReservePrivateRefCountEntry();

	/*
	 * Check whether buffer needs writing.
	 *
	 * We can make this check without taking the buffer content lock so long
	 * as we mark pages dirty in access methods *before* logging changes with
	 * XLogInsert(): if someone marks the buffer dirty just after our check we
	 * don't worry because our checkpoint.redo points before log record for
	 * upcoming changes and so we are not required to write such dirty buffer.
	 */
	buf_state = LockBufHdr(bufHdr);

	if (BUF_STATE_GET_REFCOUNT(buf_state) == 0 &&
		BUF_STATE_GET_USAGECOUNT(buf_state) == 0)
	{
		result |= BUF_REUSABLE;
	}
	else if (skip_recently_used)
	{
		/* Caller told us not to write recently-used buffers */
		UnlockBufHdr(bufHdr, buf_state);
		return result;
	}

	if (!(buf_state & BM_VALID) || !(buf_state & BM_DIRTY))
	{
		/* It's clean, so nothing to do */
		UnlockBufHdr(bufHdr, buf_state);
		return result;
	}

	/*
	 * Pin it, share-lock it, write it.  (FlushBuffer will do nothing if the
	 * buffer is clean by the time we've locked it.)
	 */
	PinBuffer_Locked(bufHdr);
	LWLockAcquire(BufferDescriptorGetContentLock(bufHdr), LW_SHARED);

	FlushBuffer(bufHdr, NULL);

	LWLockRelease(BufferDescriptorGetContentLock(bufHdr));

	tag = bufHdr->tag;

	UnpinBuffer(bufHdr, true);

	ScheduleBufferTagForWriteback(wb_context, &tag);

	return result | BUF_WRITTEN;
}