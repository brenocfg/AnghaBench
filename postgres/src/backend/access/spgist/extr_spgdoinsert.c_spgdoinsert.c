#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_76__   TYPE_9__ ;
typedef  struct TYPE_75__   TYPE_8__ ;
typedef  struct TYPE_74__   TYPE_6__ ;
typedef  struct TYPE_73__   TYPE_5__ ;
typedef  struct TYPE_72__   TYPE_57__ ;
typedef  struct TYPE_71__   TYPE_4__ ;
typedef  struct TYPE_70__   TYPE_3__ ;
typedef  struct TYPE_69__   TYPE_2__ ;
typedef  struct TYPE_68__   TYPE_1__ ;
typedef  struct TYPE_67__   TYPE_12__ ;
typedef  struct TYPE_66__   TYPE_11__ ;
typedef  struct TYPE_65__   TYPE_10__ ;

/* Type definitions */
struct TYPE_69__ {int /*<<< orphan*/  nodeLabel; int /*<<< orphan*/  nodeN; } ;
struct TYPE_68__ {int nodeN; int levelAdd; void* restDatum; } ;
struct TYPE_70__ {TYPE_2__ addNode; TYPE_1__ matchNode; } ;
struct TYPE_74__ {int level; int hasPrefix; int nNodes; int resultType; TYPE_3__ result; int /*<<< orphan*/ * nodeLabels; int /*<<< orphan*/  prefixDatum; scalar_t__ allTheSame; void* leafDatum; void* datum; } ;
typedef  TYPE_6__ spgChooseOut ;
typedef  TYPE_6__ spgChooseIn ;
typedef  int /*<<< orphan*/  out ;
struct TYPE_76__ {int size; } ;
struct TYPE_72__ {scalar_t__ type; } ;
struct TYPE_73__ {int /*<<< orphan*/  longValuesOK; } ;
struct TYPE_71__ {scalar_t__ type; int attlen; } ;
struct TYPE_75__ {TYPE_57__ attLeafType; TYPE_5__ config; TYPE_4__ attType; } ;
struct TYPE_67__ {int /*<<< orphan*/ * rd_indcollation; } ;
struct TYPE_66__ {scalar_t__ blkno; scalar_t__ buffer; int node; int /*<<< orphan*/  offnum; int /*<<< orphan*/ * page; } ;
struct TYPE_65__ {scalar_t__ prefixSize; int nNodes; scalar_t__ allTheSame; } ;
typedef  TYPE_8__ SpGistState ;
typedef  TYPE_9__* SpGistLeafTuple ;
typedef  TYPE_10__* SpGistInnerTuple ;
typedef  TYPE_11__ SPPageDesc ;
typedef  TYPE_12__* Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/ * BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ConditionalLockBuffer (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 void* FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*) ; 
 int GBUF_LEAF ; 
 int GBUF_NULLS ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Min (int,int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 TYPE_6__* PG_DETOAST_DATUM (void*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* PointerGetDatum (TYPE_6__*) ; 
 void* ReadBuffer (TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_12__*) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int SGDTSIZE ; 
 int /*<<< orphan*/  SGITDATUM (TYPE_10__*,TYPE_8__*) ; 
 int SGLTHDRSZ ; 
 int /*<<< orphan*/  SPGIST_CHOOSE_PROC ; 
 int /*<<< orphan*/  SPGIST_COMPRESS_PROC ; 
 scalar_t__ SPGIST_NULL_BLKNO ; 
 int SPGIST_PAGE_CAPACITY ; 
 scalar_t__ SPGIST_ROOT_BLKNO ; 
 scalar_t__ SpGistGetBuffer (TYPE_12__*,int,int /*<<< orphan*/ ,int*) ; 
 int SpGistGetTypeSize (TYPE_57__*,void*) ; 
 int SpGistPageGetFreeSpace (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SpGistPageIsLeaf (int /*<<< orphan*/ *) ; 
 int SpGistPageStoresNulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpGistSetLastUsedPage (TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  addLeafTuple (TYPE_12__*,TYPE_8__*,TYPE_9__*,TYPE_11__*,TYPE_11__*,int,int) ; 
 int checkSplitConditions (TYPE_12__*,TYPE_8__*,TYPE_11__*,int*) ; 
 scalar_t__ doPickSplit (TYPE_12__*,TYPE_8__*,TYPE_11__*,TYPE_11__*,TYPE_9__*,int,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getprocid (TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  moveLeafs (TYPE_12__*,TYPE_8__*,TYPE_11__*,TYPE_11__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  pfree (TYPE_9__*) ; 
 int random () ; 
#define  spgAddNode 130 
 int /*<<< orphan*/  spgAddNodeAction (TYPE_12__*,TYPE_8__*,TYPE_10__*,TYPE_11__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spgExtractNodeLabels (TYPE_8__*,TYPE_10__*) ; 
 TYPE_9__* spgFormLeafTuple (TYPE_8__*,int /*<<< orphan*/ ,void*,int) ; 
#define  spgMatchNode 129 
 int /*<<< orphan*/  spgMatchNodeAction (TYPE_12__*,TYPE_8__*,TYPE_10__*,TYPE_11__*,TYPE_11__*,int) ; 
 int /*<<< orphan*/  spgSplitNodeAction (TYPE_12__*,TYPE_8__*,TYPE_10__*,TYPE_11__*,TYPE_6__*) ; 
#define  spgSplitTuple 128 

bool
spgdoinsert(Relation index, SpGistState *state,
			ItemPointer heapPtr, Datum datum, bool isnull)
{
	int			level = 0;
	Datum		leafDatum;
	int			leafSize;
	SPPageDesc	current,
				parent;
	FmgrInfo   *procinfo = NULL;

	/*
	 * Look up FmgrInfo of the user-defined choose function once, to save
	 * cycles in the loop below.
	 */
	if (!isnull)
		procinfo = index_getprocinfo(index, 1, SPGIST_CHOOSE_PROC);

	/*
	 * Prepare the leaf datum to insert.
	 *
	 * If an optional "compress" method is provided, then call it to form the
	 * leaf datum from the input datum.  Otherwise store the input datum as
	 * is.  Since we don't use index_form_tuple in this AM, we have to make
	 * sure value to be inserted is not toasted; FormIndexDatum doesn't
	 * guarantee that.  But we assume the "compress" method to return an
	 * untoasted value.
	 */
	if (!isnull)
	{
		if (OidIsValid(index_getprocid(index, 1, SPGIST_COMPRESS_PROC)))
		{
			FmgrInfo   *compressProcinfo = NULL;

			compressProcinfo = index_getprocinfo(index, 1, SPGIST_COMPRESS_PROC);
			leafDatum = FunctionCall1Coll(compressProcinfo,
										  index->rd_indcollation[0],
										  datum);
		}
		else
		{
			Assert(state->attLeafType.type == state->attType.type);

			if (state->attType.attlen == -1)
				leafDatum = PointerGetDatum(PG_DETOAST_DATUM(datum));
			else
				leafDatum = datum;
		}
	}
	else
		leafDatum = (Datum) 0;

	/*
	 * Compute space needed for a leaf tuple containing the given datum.
	 *
	 * If it isn't gonna fit, and the opclass can't reduce the datum size by
	 * suffixing, bail out now rather than getting into an endless loop.
	 */
	if (!isnull)
		leafSize = SGLTHDRSZ + sizeof(ItemIdData) +
			SpGistGetTypeSize(&state->attLeafType, leafDatum);
	else
		leafSize = SGDTSIZE + sizeof(ItemIdData);

	if (leafSize > SPGIST_PAGE_CAPACITY && !state->config.longValuesOK)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("index row size %zu exceeds maximum %zu for index \"%s\"",
						leafSize - sizeof(ItemIdData),
						SPGIST_PAGE_CAPACITY - sizeof(ItemIdData),
						RelationGetRelationName(index)),
				 errhint("Values larger than a buffer page cannot be indexed.")));

	/* Initialize "current" to the appropriate root page */
	current.blkno = isnull ? SPGIST_NULL_BLKNO : SPGIST_ROOT_BLKNO;
	current.buffer = InvalidBuffer;
	current.page = NULL;
	current.offnum = FirstOffsetNumber;
	current.node = -1;

	/* "parent" is invalid for the moment */
	parent.blkno = InvalidBlockNumber;
	parent.buffer = InvalidBuffer;
	parent.page = NULL;
	parent.offnum = InvalidOffsetNumber;
	parent.node = -1;

	for (;;)
	{
		bool		isNew = false;

		/*
		 * Bail out if query cancel is pending.  We must have this somewhere
		 * in the loop since a broken opclass could produce an infinite
		 * picksplit loop.
		 */
		CHECK_FOR_INTERRUPTS();

		if (current.blkno == InvalidBlockNumber)
		{
			/*
			 * Create a leaf page.  If leafSize is too large to fit on a page,
			 * we won't actually use the page yet, but it simplifies the API
			 * for doPickSplit to always have a leaf page at hand; so just
			 * quietly limit our request to a page size.
			 */
			current.buffer =
				SpGistGetBuffer(index,
								GBUF_LEAF | (isnull ? GBUF_NULLS : 0),
								Min(leafSize, SPGIST_PAGE_CAPACITY),
								&isNew);
			current.blkno = BufferGetBlockNumber(current.buffer);
		}
		else if (parent.buffer == InvalidBuffer)
		{
			/* we hold no parent-page lock, so no deadlock is possible */
			current.buffer = ReadBuffer(index, current.blkno);
			LockBuffer(current.buffer, BUFFER_LOCK_EXCLUSIVE);
		}
		else if (current.blkno != parent.blkno)
		{
			/* descend to a new child page */
			current.buffer = ReadBuffer(index, current.blkno);

			/*
			 * Attempt to acquire lock on child page.  We must beware of
			 * deadlock against another insertion process descending from that
			 * page to our parent page (see README).  If we fail to get lock,
			 * abandon the insertion and tell our caller to start over.
			 *
			 * XXX this could be improved, because failing to get lock on a
			 * buffer is not proof of a deadlock situation; the lock might be
			 * held by a reader, or even just background writer/checkpointer
			 * process.  Perhaps it'd be worth retrying after sleeping a bit?
			 */
			if (!ConditionalLockBuffer(current.buffer))
			{
				ReleaseBuffer(current.buffer);
				UnlockReleaseBuffer(parent.buffer);
				return false;
			}
		}
		else
		{
			/* inner tuple can be stored on the same page as parent one */
			current.buffer = parent.buffer;
		}
		current.page = BufferGetPage(current.buffer);

		/* should not arrive at a page of the wrong type */
		if (isnull ? !SpGistPageStoresNulls(current.page) :
			SpGistPageStoresNulls(current.page))
			elog(ERROR, "SPGiST index page %u has wrong nulls flag",
				 current.blkno);

		if (SpGistPageIsLeaf(current.page))
		{
			SpGistLeafTuple leafTuple;
			int			nToSplit,
						sizeToSplit;

			leafTuple = spgFormLeafTuple(state, heapPtr, leafDatum, isnull);
			if (leafTuple->size + sizeof(ItemIdData) <=
				SpGistPageGetFreeSpace(current.page, 1))
			{
				/* it fits on page, so insert it and we're done */
				addLeafTuple(index, state, leafTuple,
							 &current, &parent, isnull, isNew);
				break;
			}
			else if ((sizeToSplit =
					  checkSplitConditions(index, state, &current,
										   &nToSplit)) < SPGIST_PAGE_CAPACITY / 2 &&
					 nToSplit < 64 &&
					 leafTuple->size + sizeof(ItemIdData) + sizeToSplit <= SPGIST_PAGE_CAPACITY)
			{
				/*
				 * the amount of data is pretty small, so just move the whole
				 * chain to another leaf page rather than splitting it.
				 */
				Assert(!isNew);
				moveLeafs(index, state, &current, &parent, leafTuple, isnull);
				break;			/* we're done */
			}
			else
			{
				/* picksplit */
				if (doPickSplit(index, state, &current, &parent,
								leafTuple, level, isnull, isNew))
					break;		/* doPickSplit installed new tuples */

				/* leaf tuple will not be inserted yet */
				pfree(leafTuple);

				/*
				 * current now describes new inner tuple, go insert into it
				 */
				Assert(!SpGistPageIsLeaf(current.page));
				goto process_inner_tuple;
			}
		}
		else					/* non-leaf page */
		{
			/*
			 * Apply the opclass choose function to figure out how to insert
			 * the given datum into the current inner tuple.
			 */
			SpGistInnerTuple innerTuple;
			spgChooseIn in;
			spgChooseOut out;

			/*
			 * spgAddNode and spgSplitTuple cases will loop back to here to
			 * complete the insertion operation.  Just in case the choose
			 * function is broken and produces add or split requests
			 * repeatedly, check for query cancel.
			 */
	process_inner_tuple:
			CHECK_FOR_INTERRUPTS();

			innerTuple = (SpGistInnerTuple) PageGetItem(current.page,
														PageGetItemId(current.page, current.offnum));

			in.datum = datum;
			in.leafDatum = leafDatum;
			in.level = level;
			in.allTheSame = innerTuple->allTheSame;
			in.hasPrefix = (innerTuple->prefixSize > 0);
			in.prefixDatum = SGITDATUM(innerTuple, state);
			in.nNodes = innerTuple->nNodes;
			in.nodeLabels = spgExtractNodeLabels(state, innerTuple);

			memset(&out, 0, sizeof(out));

			if (!isnull)
			{
				/* use user-defined choose method */
				FunctionCall2Coll(procinfo,
								  index->rd_indcollation[0],
								  PointerGetDatum(&in),
								  PointerGetDatum(&out));
			}
			else
			{
				/* force "match" action (to insert to random subnode) */
				out.resultType = spgMatchNode;
			}

			if (innerTuple->allTheSame)
			{
				/*
				 * It's not allowed to do an AddNode at an allTheSame tuple.
				 * Opclass must say "match", in which case we choose a random
				 * one of the nodes to descend into, or "split".
				 */
				if (out.resultType == spgAddNode)
					elog(ERROR, "cannot add a node to an allTheSame inner tuple");
				else if (out.resultType == spgMatchNode)
					out.result.matchNode.nodeN = random() % innerTuple->nNodes;
			}

			switch (out.resultType)
			{
				case spgMatchNode:
					/* Descend to N'th child node */
					spgMatchNodeAction(index, state, innerTuple,
									   &current, &parent,
									   out.result.matchNode.nodeN);
					/* Adjust level as per opclass request */
					level += out.result.matchNode.levelAdd;
					/* Replace leafDatum and recompute leafSize */
					if (!isnull)
					{
						leafDatum = out.result.matchNode.restDatum;
						leafSize = SGLTHDRSZ + sizeof(ItemIdData) +
							SpGistGetTypeSize(&state->attLeafType, leafDatum);
					}

					/*
					 * Loop around and attempt to insert the new leafDatum at
					 * "current" (which might reference an existing child
					 * tuple, or might be invalid to force us to find a new
					 * page for the tuple).
					 *
					 * Note: if the opclass sets longValuesOK, we rely on the
					 * choose function to eventually shorten the leafDatum
					 * enough to fit on a page.  We could add a test here to
					 * complain if the datum doesn't get visibly shorter each
					 * time, but that could get in the way of opclasses that
					 * "simplify" datums in a way that doesn't necessarily
					 * lead to physical shortening on every cycle.
					 */
					break;
				case spgAddNode:
					/* AddNode is not sensible if nodes don't have labels */
					if (in.nodeLabels == NULL)
						elog(ERROR, "cannot add a node to an inner tuple without node labels");
					/* Add node to inner tuple, per request */
					spgAddNodeAction(index, state, innerTuple,
									 &current, &parent,
									 out.result.addNode.nodeN,
									 out.result.addNode.nodeLabel);

					/*
					 * Retry insertion into the enlarged node.  We assume that
					 * we'll get a MatchNode result this time.
					 */
					goto process_inner_tuple;
					break;
				case spgSplitTuple:
					/* Split inner tuple, per request */
					spgSplitNodeAction(index, state, innerTuple,
									   &current, &out);

					/* Retry insertion into the split node */
					goto process_inner_tuple;
					break;
				default:
					elog(ERROR, "unrecognized SPGiST choose result: %d",
						 (int) out.resultType);
					break;
			}
		}
	}							/* end loop */

	/*
	 * Release any buffers we're still holding.  Beware of possibility that
	 * current and parent reference same buffer.
	 */
	if (current.buffer != InvalidBuffer)
	{
		SpGistSetLastUsedPage(index, current.buffer);
		UnlockReleaseBuffer(current.buffer);
	}
	if (parent.buffer != InvalidBuffer &&
		parent.buffer != current.buffer)
	{
		SpGistSetLastUsedPage(index, parent.buffer);
		UnlockReleaseBuffer(parent.buffer);
	}

	return true;
}