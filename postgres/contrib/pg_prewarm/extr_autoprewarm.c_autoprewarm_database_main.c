#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_11__ {int prewarm_start_idx; int prewarm_stop_idx; int /*<<< orphan*/  prewarmed_blocks; int /*<<< orphan*/  database; int /*<<< orphan*/  block_info_handle; } ;
struct TYPE_10__ {scalar_t__ database; scalar_t__ filenode; scalar_t__ forknum; scalar_t__ blocknum; int /*<<< orphan*/  tablespace; } ;
struct TYPE_9__ {int /*<<< orphan*/  rd_smgr; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__ BlockInfoRecord ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerInitializeConnectionByOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidForkNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ MAX_FORKNUM ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RelationGetNumberOfBlocksInFork (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelidByRelfilenode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  apw_init_shmem () ; 
 TYPE_5__* apw_state ; 
 int /*<<< orphan*/  die ; 
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ have_free_buffer () ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ smgrexists (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* try_relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
autoprewarm_database_main(Datum main_arg)
{
	int			pos;
	BlockInfoRecord *block_info;
	Relation	rel = NULL;
	BlockNumber nblocks = 0;
	BlockInfoRecord *old_blk = NULL;
	dsm_segment *seg;

	/* Establish signal handlers; once that's done, unblock signals. */
	pqsignal(SIGTERM, die);
	BackgroundWorkerUnblockSignals();

	/* Connect to correct database and get block information. */
	apw_init_shmem();
	seg = dsm_attach(apw_state->block_info_handle);
	if (seg == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("could not map dynamic shared memory segment")));
	BackgroundWorkerInitializeConnectionByOid(apw_state->database, InvalidOid, 0);
	block_info = (BlockInfoRecord *) dsm_segment_address(seg);
	pos = apw_state->prewarm_start_idx;

	/*
	 * Loop until we run out of blocks to prewarm or until we run out of free
	 * buffers.
	 */
	while (pos < apw_state->prewarm_stop_idx && have_free_buffer())
	{
		BlockInfoRecord *blk = &block_info[pos++];
		Buffer		buf;

		CHECK_FOR_INTERRUPTS();

		/*
		 * Quit if we've reached records for another database. If previous
		 * blocks are of some global objects, then continue pre-warming.
		 */
		if (old_blk != NULL && old_blk->database != blk->database &&
			old_blk->database != 0)
			break;

		/*
		 * As soon as we encounter a block of a new relation, close the old
		 * relation. Note that rel will be NULL if try_relation_open failed
		 * previously; in that case, there is nothing to close.
		 */
		if (old_blk != NULL && old_blk->filenode != blk->filenode &&
			rel != NULL)
		{
			relation_close(rel, AccessShareLock);
			rel = NULL;
			CommitTransactionCommand();
		}

		/*
		 * Try to open each new relation, but only once, when we first
		 * encounter it. If it's been dropped, skip the associated blocks.
		 */
		if (old_blk == NULL || old_blk->filenode != blk->filenode)
		{
			Oid			reloid;

			Assert(rel == NULL);
			StartTransactionCommand();
			reloid = RelidByRelfilenode(blk->tablespace, blk->filenode);
			if (OidIsValid(reloid))
				rel = try_relation_open(reloid, AccessShareLock);

			if (!rel)
				CommitTransactionCommand();
		}
		if (!rel)
		{
			old_blk = blk;
			continue;
		}

		/* Once per fork, check for fork existence and size. */
		if (old_blk == NULL ||
			old_blk->filenode != blk->filenode ||
			old_blk->forknum != blk->forknum)
		{
			RelationOpenSmgr(rel);

			/*
			 * smgrexists is not safe for illegal forknum, hence check whether
			 * the passed forknum is valid before using it in smgrexists.
			 */
			if (blk->forknum > InvalidForkNumber &&
				blk->forknum <= MAX_FORKNUM &&
				smgrexists(rel->rd_smgr, blk->forknum))
				nblocks = RelationGetNumberOfBlocksInFork(rel, blk->forknum);
			else
				nblocks = 0;
		}

		/* Check whether blocknum is valid and within fork file size. */
		if (blk->blocknum >= nblocks)
		{
			/* Move to next forknum. */
			old_blk = blk;
			continue;
		}

		/* Prewarm buffer. */
		buf = ReadBufferExtended(rel, blk->forknum, blk->blocknum, RBM_NORMAL,
								 NULL);
		if (BufferIsValid(buf))
		{
			apw_state->prewarmed_blocks++;
			ReleaseBuffer(buf);
		}

		old_blk = blk;
	}

	dsm_detach(seg);

	/* Release lock on previous relation. */
	if (rel)
	{
		relation_close(rel, AccessShareLock);
		CommitTransactionCommand();
	}
}