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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_9__ {double m; } ;
struct TYPE_8__ {int /*<<< orphan*/  randstate; } ;
typedef  TYPE_1__ ReservoirStateData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ BlockSamplerData ;
typedef  double BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BlockSampler_HasMore (TYPE_2__*) ; 
 int /*<<< orphan*/  BlockSampler_Init (TYPE_2__*,double,int,int /*<<< orphan*/ ) ; 
 double BlockSampler_Next (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecCopySlotHeapTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetOldestXmin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCARRAY_FLAGS_VACUUM ; 
 double RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_rows ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,double,double,double,double,int,double) ; 
 double floor (double) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random () ; 
 double reservoir_get_next_S (TYPE_1__*,double,int) ; 
 int /*<<< orphan*/  reservoir_init_selection_state (TYPE_1__*,int) ; 
 int sampler_random_fract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_analyze (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_scan_analyze_next_block (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 scalar_t__ table_scan_analyze_next_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * table_slot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vac_strategy ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

__attribute__((used)) static int
acquire_sample_rows(Relation onerel, int elevel,
					HeapTuple *rows, int targrows,
					double *totalrows, double *totaldeadrows)
{
	int			numrows = 0;	/* # rows now in reservoir */
	double		samplerows = 0; /* total # rows collected */
	double		liverows = 0;	/* # live rows seen */
	double		deadrows = 0;	/* # dead rows seen */
	double		rowstoskip = -1;	/* -1 means not set yet */
	BlockNumber totalblocks;
	TransactionId OldestXmin;
	BlockSamplerData bs;
	ReservoirStateData rstate;
	TupleTableSlot *slot;
	TableScanDesc scan;

	Assert(targrows > 0);

	totalblocks = RelationGetNumberOfBlocks(onerel);

	/* Need a cutoff xmin for HeapTupleSatisfiesVacuum */
	OldestXmin = GetOldestXmin(onerel, PROCARRAY_FLAGS_VACUUM);

	/* Prepare for sampling block numbers */
	BlockSampler_Init(&bs, totalblocks, targrows, random());
	/* Prepare for sampling rows */
	reservoir_init_selection_state(&rstate, targrows);

	scan = table_beginscan_analyze(onerel);
	slot = table_slot_create(onerel, NULL);

	/* Outer loop over blocks to sample */
	while (BlockSampler_HasMore(&bs))
	{
		BlockNumber targblock = BlockSampler_Next(&bs);

		vacuum_delay_point();

		if (!table_scan_analyze_next_block(scan, targblock, vac_strategy))
			continue;

		while (table_scan_analyze_next_tuple(scan, OldestXmin, &liverows, &deadrows, slot))
		{
			/*
			 * The first targrows sample rows are simply copied into the
			 * reservoir. Then we start replacing tuples in the sample until
			 * we reach the end of the relation.  This algorithm is from Jeff
			 * Vitter's paper (see full citation in utils/misc/sampling.c). It
			 * works by repeatedly computing the number of tuples to skip
			 * before selecting a tuple, which replaces a randomly chosen
			 * element of the reservoir (current set of tuples).  At all times
			 * the reservoir is a true random sample of the tuples we've
			 * passed over so far, so when we fall off the end of the relation
			 * we're done.
			 */
			if (numrows < targrows)
				rows[numrows++] = ExecCopySlotHeapTuple(slot);
			else
			{
				/*
				 * t in Vitter's paper is the number of records already
				 * processed.  If we need to compute a new S value, we must
				 * use the not-yet-incremented value of samplerows as t.
				 */
				if (rowstoskip < 0)
					rowstoskip = reservoir_get_next_S(&rstate, samplerows, targrows);

				if (rowstoskip <= 0)
				{
					/*
					 * Found a suitable tuple, so save it, replacing one old
					 * tuple at random
					 */
					int			k = (int) (targrows * sampler_random_fract(rstate.randstate));

					Assert(k >= 0 && k < targrows);
					heap_freetuple(rows[k]);
					rows[k] = ExecCopySlotHeapTuple(slot);
				}

				rowstoskip -= 1;
			}

			samplerows += 1;
		}
	}

	ExecDropSingleTupleTableSlot(slot);
	table_endscan(scan);

	/*
	 * If we didn't find as many tuples as we wanted then we're done. No sort
	 * is needed, since they're already in order.
	 *
	 * Otherwise we need to sort the collected tuples by position
	 * (itempointer). It's not worth worrying about corner cases where the
	 * tuples are already sorted.
	 */
	if (numrows == targrows)
		qsort((void *) rows, numrows, sizeof(HeapTuple), compare_rows);

	/*
	 * Estimate total numbers of live and dead rows in relation, extrapolating
	 * on the assumption that the average tuple density in pages we didn't
	 * scan is the same as in the pages we did scan.  Since what we scanned is
	 * a random sample of the pages in the relation, this should be a good
	 * assumption.
	 */
	if (bs.m > 0)
	{
		*totalrows = floor((liverows / bs.m) * totalblocks + 0.5);
		*totaldeadrows = floor((deadrows / bs.m) * totalblocks + 0.5);
	}
	else
	{
		*totalrows = 0.0;
		*totaldeadrows = 0.0;
	}

	/*
	 * Emit some interesting relation info
	 */
	ereport(elevel,
			(errmsg("\"%s\": scanned %d of %u pages, "
					"containing %.0f live rows and %.0f dead rows; "
					"%d rows in sample, %.0f estimated total rows",
					RelationGetRelationName(onerel),
					bs.m, totalblocks,
					liverows, deadrows,
					numrows, *totalrows)));

	return numrows;
}