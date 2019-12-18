#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int delayChkpt; } ;
struct TYPE_9__ {int /*<<< orphan*/  shared_blks_dirtied; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ BufferDesc ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_DIRTY ; 
 int BM_JUST_DIRTIED ; 
 int BM_PERMANENT ; 
 scalar_t__ BUF_STATE_GET_REFCOUNT (int) ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_1__*) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ BufferIsLocal (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetBufferDescriptor (scalar_t__) ; 
 scalar_t__ GetPrivateRefCount (scalar_t__) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int LockBufHdr (TYPE_1__*) ; 
 int /*<<< orphan*/  MarkLocalBufferDirty (scalar_t__) ; 
 TYPE_4__* MyPgXact ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_1__*,int) ; 
 scalar_t__ VacuumCostActive ; 
 int /*<<< orphan*/  VacuumCostBalance ; 
 scalar_t__ VacuumCostPageDirty ; 
 int /*<<< orphan*/  VacuumPageDirty ; 
 scalar_t__ XLogHintBitIsNeeded () ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogSaveBufferForHint (scalar_t__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__ pgBufferUsage ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

void
MarkBufferDirtyHint(Buffer buffer, bool buffer_std)
{
	BufferDesc *bufHdr;
	Page		page = BufferGetPage(buffer);

	if (!BufferIsValid(buffer))
		elog(ERROR, "bad buffer ID: %d", buffer);

	if (BufferIsLocal(buffer))
	{
		MarkLocalBufferDirty(buffer);
		return;
	}

	bufHdr = GetBufferDescriptor(buffer - 1);

	Assert(GetPrivateRefCount(buffer) > 0);
	/* here, either share or exclusive lock is OK */
	Assert(LWLockHeldByMe(BufferDescriptorGetContentLock(bufHdr)));

	/*
	 * This routine might get called many times on the same page, if we are
	 * making the first scan after commit of an xact that added/deleted many
	 * tuples. So, be as quick as we can if the buffer is already dirty.  We
	 * do this by not acquiring spinlock if it looks like the status bits are
	 * already set.  Since we make this test unlocked, there's a chance we
	 * might fail to notice that the flags have just been cleared, and failed
	 * to reset them, due to memory-ordering issues.  But since this function
	 * is only intended to be used in cases where failing to write out the
	 * data would be harmless anyway, it doesn't really matter.
	 */
	if ((pg_atomic_read_u32(&bufHdr->state) & (BM_DIRTY | BM_JUST_DIRTIED)) !=
		(BM_DIRTY | BM_JUST_DIRTIED))
	{
		XLogRecPtr	lsn = InvalidXLogRecPtr;
		bool		dirtied = false;
		bool		delayChkpt = false;
		uint32		buf_state;

		/*
		 * If we need to protect hint bit updates from torn writes, WAL-log a
		 * full page image of the page. This full page image is only necessary
		 * if the hint bit update is the first change to the page since the
		 * last checkpoint.
		 *
		 * We don't check full_page_writes here because that logic is included
		 * when we call XLogInsert() since the value changes dynamically.
		 */
		if (XLogHintBitIsNeeded() &&
			(pg_atomic_read_u32(&bufHdr->state) & BM_PERMANENT))
		{
			/*
			 * If we're in recovery we cannot dirty a page because of a hint.
			 * We can set the hint, just not dirty the page as a result so the
			 * hint is lost when we evict the page or shutdown.
			 *
			 * See src/backend/storage/page/README for longer discussion.
			 */
			if (RecoveryInProgress())
				return;

			/*
			 * If the block is already dirty because we either made a change
			 * or set a hint already, then we don't need to write a full page
			 * image.  Note that aggressive cleaning of blocks dirtied by hint
			 * bit setting would increase the call rate. Bulk setting of hint
			 * bits would reduce the call rate...
			 *
			 * We must issue the WAL record before we mark the buffer dirty.
			 * Otherwise we might write the page before we write the WAL. That
			 * causes a race condition, since a checkpoint might occur between
			 * writing the WAL record and marking the buffer dirty. We solve
			 * that with a kluge, but one that is already in use during
			 * transaction commit to prevent race conditions. Basically, we
			 * simply prevent the checkpoint WAL record from being written
			 * until we have marked the buffer dirty. We don't start the
			 * checkpoint flush until we have marked dirty, so our checkpoint
			 * must flush the change to disk successfully or the checkpoint
			 * never gets written, so crash recovery will fix.
			 *
			 * It's possible we may enter here without an xid, so it is
			 * essential that CreateCheckpoint waits for virtual transactions
			 * rather than full transactionids.
			 */
			MyPgXact->delayChkpt = delayChkpt = true;
			lsn = XLogSaveBufferForHint(buffer, buffer_std);
		}

		buf_state = LockBufHdr(bufHdr);

		Assert(BUF_STATE_GET_REFCOUNT(buf_state) > 0);

		if (!(buf_state & BM_DIRTY))
		{
			dirtied = true;		/* Means "will be dirtied by this action" */

			/*
			 * Set the page LSN if we wrote a backup block. We aren't supposed
			 * to set this when only holding a share lock but as long as we
			 * serialise it somehow we're OK. We choose to set LSN while
			 * holding the buffer header lock, which causes any reader of an
			 * LSN who holds only a share lock to also obtain a buffer header
			 * lock before using PageGetLSN(), which is enforced in
			 * BufferGetLSNAtomic().
			 *
			 * If checksums are enabled, you might think we should reset the
			 * checksum here. That will happen when the page is written
			 * sometime later in this checkpoint cycle.
			 */
			if (!XLogRecPtrIsInvalid(lsn))
				PageSetLSN(page, lsn);
		}

		buf_state |= BM_DIRTY | BM_JUST_DIRTIED;
		UnlockBufHdr(bufHdr, buf_state);

		if (delayChkpt)
			MyPgXact->delayChkpt = false;

		if (dirtied)
		{
			VacuumPageDirty++;
			pgBufferUsage.shared_blks_dirtied++;
			if (VacuumCostActive)
				VacuumCostBalance += VacuumCostPageDirty;
		}
	}
}