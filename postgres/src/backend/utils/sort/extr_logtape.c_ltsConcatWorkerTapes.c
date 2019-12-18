#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long int64 ;
struct TYPE_6__ {int /*<<< orphan*/  firstblocknumber; } ;
typedef  TYPE_1__ TapeShare ;
struct TYPE_8__ {long offsetBlockNumber; int /*<<< orphan*/  max_size; int /*<<< orphan*/  firstBlockNumber; } ;
struct TYPE_7__ {int nTapes; long nBlocksAllocated; long nBlocksWritten; long nHoleBlocks; int /*<<< orphan*/ * pfile; TYPE_3__* tapes; } ;
typedef  int /*<<< orphan*/  SharedFileSet ;
typedef  TYPE_2__ LogicalTapeSet ;
typedef  TYPE_3__ LogicalTape ;
typedef  int /*<<< orphan*/  BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 long BLCKSZ ; 
 long BufFileAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufFileOpenShared (int /*<<< orphan*/ *,char*) ; 
 long BufFileSize (int /*<<< orphan*/ *) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  MaxAllocSize ; 
 int /*<<< orphan*/  Min (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  pg_itoa (int,char*) ; 

__attribute__((used)) static void
ltsConcatWorkerTapes(LogicalTapeSet *lts, TapeShare *shared,
					 SharedFileSet *fileset)
{
	LogicalTape *lt = NULL;
	long		tapeblocks = 0L;
	long		nphysicalblocks = 0L;
	int			i;

	/* Should have at least one worker tape, plus leader's tape */
	Assert(lts->nTapes >= 2);

	/*
	 * Build concatenated view of all BufFiles, remembering the block number
	 * where each source file begins.  No changes are needed for leader/last
	 * tape.
	 */
	for (i = 0; i < lts->nTapes - 1; i++)
	{
		char		filename[MAXPGPATH];
		BufFile    *file;
		int64		filesize;

		lt = &lts->tapes[i];

		pg_itoa(i, filename);
		file = BufFileOpenShared(fileset, filename);
		filesize = BufFileSize(file);

		/*
		 * Stash first BufFile, and concatenate subsequent BufFiles to that.
		 * Store block offset into each tape as we go.
		 */
		lt->firstBlockNumber = shared[i].firstblocknumber;
		if (i == 0)
		{
			lts->pfile = file;
			lt->offsetBlockNumber = 0L;
		}
		else
		{
			lt->offsetBlockNumber = BufFileAppend(lts->pfile, file);
		}
		/* Don't allocate more for read buffer than could possibly help */
		lt->max_size = Min(MaxAllocSize, filesize);
		tapeblocks = filesize / BLCKSZ;
		nphysicalblocks += tapeblocks;
	}

	/*
	 * Set # of allocated blocks, as well as # blocks written.  Use extent of
	 * new BufFile space (from 0 to end of last worker's tape space) for this.
	 * Allocated/written blocks should include space used by holes left
	 * between concatenated BufFiles.
	 */
	lts->nBlocksAllocated = lt->offsetBlockNumber + tapeblocks;
	lts->nBlocksWritten = lts->nBlocksAllocated;

	/*
	 * Compute number of hole blocks so that we can later work backwards, and
	 * instrument number of physical blocks.  We don't simply use physical
	 * blocks directly for instrumentation because this would break if we ever
	 * subsequently wrote to the leader tape.
	 *
	 * Working backwards like this keeps our options open.  If shared BufFiles
	 * ever support being written to post-export, logtape.c can automatically
	 * take advantage of that.  We'd then support writing to the leader tape
	 * while recycling space from worker tapes, because the leader tape has a
	 * zero offset (write routines won't need to have extra logic to apply an
	 * offset).
	 *
	 * The only thing that currently prevents writing to the leader tape from
	 * working is the fact that BufFiles opened using BufFileOpenShared() are
	 * read-only by definition, but that could be changed if it seemed
	 * worthwhile.  For now, writing to the leader tape will raise a "Bad file
	 * descriptor" error, so tuplesort must avoid writing to the leader tape
	 * altogether.
	 */
	lts->nHoleBlocks = lts->nBlocksAllocated - nphysicalblocks;
}