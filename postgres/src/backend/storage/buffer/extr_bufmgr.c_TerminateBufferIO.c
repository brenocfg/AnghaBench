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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  BufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_CHECKPOINT_NEEDED ; 
 int BM_DIRTY ; 
 int BM_IO_ERROR ; 
 int BM_IO_IN_PROGRESS ; 
 int BM_JUST_DIRTIED ; 
 int /*<<< orphan*/  BufferDescriptorGetIOLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InProgressBuf ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int LockBufHdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockBufHdr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
TerminateBufferIO(BufferDesc *buf, bool clear_dirty, uint32 set_flag_bits)
{
	uint32		buf_state;

	Assert(buf == InProgressBuf);

	buf_state = LockBufHdr(buf);

	Assert(buf_state & BM_IO_IN_PROGRESS);

	buf_state &= ~(BM_IO_IN_PROGRESS | BM_IO_ERROR);
	if (clear_dirty && !(buf_state & BM_JUST_DIRTIED))
		buf_state &= ~(BM_DIRTY | BM_CHECKPOINT_NEEDED);

	buf_state |= set_flag_bits;
	UnlockBufHdr(buf, buf_state);

	InProgressBuf = NULL;

	LWLockRelease(BufferDescriptorGetIOLock(buf));
}