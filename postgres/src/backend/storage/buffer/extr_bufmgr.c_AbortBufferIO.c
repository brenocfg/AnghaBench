#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  blockNum; int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; } ;
struct TYPE_9__ {TYPE_1__ tag; } ;
typedef  TYPE_2__ BufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_DIRTY ; 
 int BM_IO_ERROR ; 
 int BM_IO_IN_PROGRESS ; 
 int BM_VALID ; 
 int /*<<< orphan*/  BufferDescriptorGetIOLock (TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_IO_ERROR ; 
 TYPE_2__* InProgressBuf ; 
 scalar_t__ IsForInput ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int LockBufHdr (TYPE_2__*) ; 
 int /*<<< orphan*/  TerminateBufferIO (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpathperm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AbortBufferIO(void)
{
	BufferDesc *buf = InProgressBuf;

	if (buf)
	{
		uint32		buf_state;

		/*
		 * Since LWLockReleaseAll has already been called, we're not holding
		 * the buffer's io_in_progress_lock. We have to re-acquire it so that
		 * we can use TerminateBufferIO. Anyone who's executing WaitIO on the
		 * buffer will be in a busy spin until we succeed in doing this.
		 */
		LWLockAcquire(BufferDescriptorGetIOLock(buf), LW_EXCLUSIVE);

		buf_state = LockBufHdr(buf);
		Assert(buf_state & BM_IO_IN_PROGRESS);
		if (IsForInput)
		{
			Assert(!(buf_state & BM_DIRTY));

			/* We'd better not think buffer is valid yet */
			Assert(!(buf_state & BM_VALID));
			UnlockBufHdr(buf, buf_state);
		}
		else
		{
			Assert(buf_state & BM_DIRTY);
			UnlockBufHdr(buf, buf_state);
			/* Issue notice if this is not the first failure... */
			if (buf_state & BM_IO_ERROR)
			{
				/* Buffer is pinned, so we can read tag without spinlock */
				char	   *path;

				path = relpathperm(buf->tag.rnode, buf->tag.forkNum);
				ereport(WARNING,
						(errcode(ERRCODE_IO_ERROR),
						 errmsg("could not write block %u of %s",
								buf->tag.blockNum, path),
						 errdetail("Multiple failures --- write error might be permanent.")));
				pfree(path);
			}
		}
		TerminateBufferIO(buf, false, BM_IO_ERROR);
	}
}