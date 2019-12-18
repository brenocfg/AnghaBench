#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pagesPerRange; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ xl_brin_createidx ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {double bs_numtuples; int /*<<< orphan*/  bs_rmAccess; } ;
struct TYPE_9__ {double heap_tuples; double index_tuples; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  TYPE_2__ IndexBuildResult ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  TYPE_3__ BrinBuildState ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BRIN_CURRENT_VERSION ; 
 scalar_t__ BRIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BrinGetPagesPerRange (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_NEW ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BRIN_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeOfBrinCreateIdx ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_BRIN_CREATE_INDEX ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brinRevmapInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brinRevmapTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_metapage_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brinbuildCallback ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  form_and_insert_tuple (TYPE_3__*) ; 
 TYPE_3__* initialize_brin_buildstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 double table_index_build_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate_brin_buildstate (TYPE_3__*) ; 

IndexBuildResult *
brinbuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;
	double		reltuples;
	double		idxtuples;
	BrinRevmap *revmap;
	BrinBuildState *state;
	Buffer		meta;
	BlockNumber pagesPerRange;

	/*
	 * We expect to be called exactly once for any index relation.
	 */
	if (RelationGetNumberOfBlocks(index) != 0)
		elog(ERROR, "index \"%s\" already contains data",
			 RelationGetRelationName(index));

	/*
	 * Critical section not required, because on error the creation of the
	 * whole relation will be rolled back.
	 */

	meta = ReadBuffer(index, P_NEW);
	Assert(BufferGetBlockNumber(meta) == BRIN_METAPAGE_BLKNO);
	LockBuffer(meta, BUFFER_LOCK_EXCLUSIVE);

	brin_metapage_init(BufferGetPage(meta), BrinGetPagesPerRange(index),
					   BRIN_CURRENT_VERSION);
	MarkBufferDirty(meta);

	if (RelationNeedsWAL(index))
	{
		xl_brin_createidx xlrec;
		XLogRecPtr	recptr;
		Page		page;

		xlrec.version = BRIN_CURRENT_VERSION;
		xlrec.pagesPerRange = BrinGetPagesPerRange(index);

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBrinCreateIdx);
		XLogRegisterBuffer(0, meta, REGBUF_WILL_INIT | REGBUF_STANDARD);

		recptr = XLogInsert(RM_BRIN_ID, XLOG_BRIN_CREATE_INDEX);

		page = BufferGetPage(meta);
		PageSetLSN(page, recptr);
	}

	UnlockReleaseBuffer(meta);

	/*
	 * Initialize our state, including the deformed tuple state.
	 */
	revmap = brinRevmapInitialize(index, &pagesPerRange, NULL);
	state = initialize_brin_buildstate(index, revmap, pagesPerRange);

	/*
	 * Now scan the relation.  No syncscan allowed here because we want the
	 * heap blocks in physical order.
	 */
	reltuples = table_index_build_scan(heap, index, indexInfo, false, true,
									   brinbuildCallback, (void *) state, NULL);

	/* process the final batch */
	form_and_insert_tuple(state);

	/* release resources */
	idxtuples = state->bs_numtuples;
	brinRevmapTerminate(state->bs_rmAccess);
	terminate_brin_buildstate(state);

	/*
	 * Return statistics
	 */
	result = (IndexBuildResult *) palloc(sizeof(IndexBuildResult));

	result->heap_tuples = reltuples;
	result->index_tuples = idxtuples;

	return result;
}