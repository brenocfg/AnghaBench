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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_FORCE_IMAGE ; 
 int REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_FPI ; 
 int XLR_MAX_BLOCK_ID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogEnsureRecordSpace (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 

void
log_newpage_range(Relation rel, ForkNumber forkNum,
				  BlockNumber startblk, BlockNumber endblk,
				  bool page_std)
{
	BlockNumber blkno;

	/*
	 * Iterate over all the pages in the range. They are collected into
	 * batches of XLR_MAX_BLOCK_ID pages, and a single WAL-record is written
	 * for each batch.
	 */
	XLogEnsureRecordSpace(XLR_MAX_BLOCK_ID - 1, 0);

	blkno = startblk;
	while (blkno < endblk)
	{
		Buffer		bufpack[XLR_MAX_BLOCK_ID];
		XLogRecPtr	recptr;
		int			nbufs;
		int			i;

		CHECK_FOR_INTERRUPTS();

		/* Collect a batch of blocks. */
		nbufs = 0;
		while (nbufs < XLR_MAX_BLOCK_ID && blkno < endblk)
		{
			Buffer		buf = ReadBuffer(rel, blkno);

			LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

			/*
			 * Completely empty pages are not WAL-logged. Writing a WAL record
			 * would change the LSN, and we don't want that. We want the page
			 * to stay empty.
			 */
			if (!PageIsNew(BufferGetPage(buf)))
				bufpack[nbufs++] = buf;
			else
				UnlockReleaseBuffer(buf);
			blkno++;
		}

		/* Write WAL record for this batch. */
		XLogBeginInsert();

		START_CRIT_SECTION();
		for (i = 0; i < nbufs; i++)
		{
			XLogRegisterBuffer(i, bufpack[i], REGBUF_FORCE_IMAGE | REGBUF_STANDARD);
			MarkBufferDirty(bufpack[i]);
		}

		recptr = XLogInsert(RM_XLOG_ID, XLOG_FPI);

		for (i = 0; i < nbufs; i++)
		{
			PageSetLSN(BufferGetPage(bufpack[i]), recptr);
			UnlockReleaseBuffer(bufpack[i]);
		}
		END_CRIT_SECTION();
	}
}