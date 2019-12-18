#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  node; int /*<<< orphan*/  backend; } ;
struct TYPE_11__ {TYPE_1__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  scalar_t__ Page ;
typedef  TYPE_3__ PGAlignedBlock ;
typedef  scalar_t__ ForkNumber ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INIT_FORKNUM ; 
 int /*<<< orphan*/  PageIsVerified (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PageSetChecksumInplace (scalar_t__,scalar_t__) ; 
 char RELPERSISTENCE_PERMANENT ; 
 char RELPERSISTENCE_UNLOGGED ; 
 scalar_t__ XLogIsNeeded () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  relpathbackend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smgrextend (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  smgrimmedsync (TYPE_2__*,scalar_t__) ; 
 scalar_t__ smgrnblocks (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  smgrread (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 

void
RelationCopyStorage(SMgrRelation src, SMgrRelation dst,
					ForkNumber forkNum, char relpersistence)
{
	PGAlignedBlock buf;
	Page		page;
	bool		use_wal;
	bool		copying_initfork;
	BlockNumber nblocks;
	BlockNumber blkno;

	page = (Page) buf.data;

	/*
	 * The init fork for an unlogged relation in many respects has to be
	 * treated the same as normal relation, changes need to be WAL logged and
	 * it needs to be synced to disk.
	 */
	copying_initfork = relpersistence == RELPERSISTENCE_UNLOGGED &&
		forkNum == INIT_FORKNUM;

	/*
	 * We need to log the copied data in WAL iff WAL archiving/streaming is
	 * enabled AND it's a permanent relation.
	 */
	use_wal = XLogIsNeeded() &&
		(relpersistence == RELPERSISTENCE_PERMANENT || copying_initfork);

	nblocks = smgrnblocks(src, forkNum);

	for (blkno = 0; blkno < nblocks; blkno++)
	{
		/* If we got a cancel signal during the copy of the data, quit */
		CHECK_FOR_INTERRUPTS();

		smgrread(src, forkNum, blkno, buf.data);

		if (!PageIsVerified(page, blkno))
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("invalid page in block %u of relation %s",
							blkno,
							relpathbackend(src->smgr_rnode.node,
										   src->smgr_rnode.backend,
										   forkNum))));

		/*
		 * WAL-log the copied page. Unfortunately we don't know what kind of a
		 * page this is, so we have to log the full page including any unused
		 * space.
		 */
		if (use_wal)
			log_newpage(&dst->smgr_rnode.node, forkNum, blkno, page, false);

		PageSetChecksumInplace(page, blkno);

		/*
		 * Now write the page.  We say skipFsync = true because there's no
		 * need for smgr to schedule an fsync for this write; we'll do it
		 * ourselves below.
		 */
		smgrextend(dst, forkNum, blkno, buf.data, true);
	}

	/*
	 * If the rel is WAL-logged, must fsync before commit.  We use heap_sync
	 * to ensure that the toast table gets fsync'd too.  (For a temp or
	 * unlogged rel we don't care since the data will be gone after a crash
	 * anyway.)
	 *
	 * It's obvious that we must do this when not WAL-logging the copy. It's
	 * less obvious that we have to do it even if we did WAL-log the copied
	 * pages. The reason is that since we're copying outside shared buffers, a
	 * CHECKPOINT occurring during the copy has no way to flush the previously
	 * written data to disk (indeed it won't know the new rel even exists).  A
	 * crash later on would replay WAL from the checkpoint, therefore it
	 * wouldn't replay our earlier WAL entries. If we do not fsync those pages
	 * here, they might still not be on disk when the crash occurs.
	 */
	if (relpersistence == RELPERSISTENCE_PERMANENT || copying_initfork)
		smgrimmedsync(dst, forkNum);
}