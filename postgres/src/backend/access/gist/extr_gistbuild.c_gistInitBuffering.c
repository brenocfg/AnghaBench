#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int natts; } ;
struct TYPE_11__ {scalar_t__ attlen; } ;
struct TYPE_10__ {int freespace; int /*<<< orphan*/  bufferingMode; int /*<<< orphan*/  gfbb; scalar_t__ indtuples; scalar_t__ indtuplesSize; TYPE_1__* indexrel; } ;
struct TYPE_9__ {TYPE_8__* rd_att; } ;
typedef  double Size ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  int /*<<< orphan*/  GISTPageOpaqueData ;
typedef  TYPE_2__ GISTBuildState ;

/* Variables and functions */
 double BLCKSZ ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  GIST_BUFFERING_ACTIVE ; 
 int /*<<< orphan*/  GIST_BUFFERING_DISABLED ; 
 scalar_t__ MAXALIGN (int) ; 
 int SizeOfPageHeaderData ; 
 TYPE_7__* TupleDescAttr (TYPE_8__*,int) ; 
 scalar_t__ VARHDRSZ ; 
 int calculatePagesPerBuffer (TYPE_2__*,int) ; 
 int effective_cache_size ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gistGetMaxLevel (TYPE_1__*) ; 
 int /*<<< orphan*/  gistInitBuildBuffers (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistInitParentMap (TYPE_2__*) ; 
 scalar_t__ maintenance_work_mem ; 
 int pow (double,double) ; 

__attribute__((used)) static void
gistInitBuffering(GISTBuildState *buildstate)
{
	Relation	index = buildstate->indexrel;
	int			pagesPerBuffer;
	Size		pageFreeSpace;
	Size		itupAvgSize,
				itupMinSize;
	double		avgIndexTuplesPerPage,
				maxIndexTuplesPerPage;
	int			i;
	int			levelStep;

	/* Calc space of index page which is available for index tuples */
	pageFreeSpace = BLCKSZ - SizeOfPageHeaderData - sizeof(GISTPageOpaqueData)
		- sizeof(ItemIdData)
		- buildstate->freespace;

	/*
	 * Calculate average size of already inserted index tuples using gathered
	 * statistics.
	 */
	itupAvgSize = (double) buildstate->indtuplesSize /
		(double) buildstate->indtuples;

	/*
	 * Calculate minimal possible size of index tuple by index metadata.
	 * Minimal possible size of varlena is VARHDRSZ.
	 *
	 * XXX: that's not actually true, as a short varlen can be just 2 bytes.
	 * And we should take padding into account here.
	 */
	itupMinSize = (Size) MAXALIGN(sizeof(IndexTupleData));
	for (i = 0; i < index->rd_att->natts; i++)
	{
		if (TupleDescAttr(index->rd_att, i)->attlen < 0)
			itupMinSize += VARHDRSZ;
		else
			itupMinSize += TupleDescAttr(index->rd_att, i)->attlen;
	}

	/* Calculate average and maximal number of index tuples which fit to page */
	avgIndexTuplesPerPage = pageFreeSpace / itupAvgSize;
	maxIndexTuplesPerPage = pageFreeSpace / itupMinSize;

	/*
	 * We need to calculate two parameters for the buffering algorithm:
	 * levelStep and pagesPerBuffer.
	 *
	 * levelStep determines the size of subtree that we operate on, while
	 * emptying a buffer. A higher value is better, as you need fewer buffer
	 * emptying steps to build the index. However, if you set it too high, the
	 * subtree doesn't fit in cache anymore, and you quickly lose the benefit
	 * of the buffers.
	 *
	 * In Arge et al's paper, levelStep is chosen as logB(M/4B), where B is
	 * the number of tuples on page (ie. fanout), and M is the amount of
	 * internal memory available. Curiously, they doesn't explain *why* that
	 * setting is optimal. We calculate it by taking the highest levelStep so
	 * that a subtree still fits in cache. For a small B, our way of
	 * calculating levelStep is very close to Arge et al's formula. For a
	 * large B, our formula gives a value that is 2x higher.
	 *
	 * The average size (in pages) of a subtree of depth n can be calculated
	 * as a geometric series:
	 *
	 * B^0 + B^1 + B^2 + ... + B^n = (1 - B^(n + 1)) / (1 - B)
	 *
	 * where B is the average number of index tuples on page. The subtree is
	 * cached in the shared buffer cache and the OS cache, so we choose
	 * levelStep so that the subtree size is comfortably smaller than
	 * effective_cache_size, with a safety factor of 4.
	 *
	 * The estimate on the average number of index tuples on page is based on
	 * average tuple sizes observed before switching to buffered build, so the
	 * real subtree size can be somewhat larger. Also, it would selfish to
	 * gobble the whole cache for our index build. The safety factor of 4
	 * should account for those effects.
	 *
	 * The other limiting factor for setting levelStep is that while
	 * processing a subtree, we need to hold one page for each buffer at the
	 * next lower buffered level. The max. number of buffers needed for that
	 * is maxIndexTuplesPerPage^levelStep. This is very conservative, but
	 * hopefully maintenance_work_mem is set high enough that you're
	 * constrained by effective_cache_size rather than maintenance_work_mem.
	 *
	 * XXX: the buffer hash table consumes a fair amount of memory too per
	 * buffer, but that is not currently taken into account. That scales on
	 * the total number of buffers used, ie. the index size and on levelStep.
	 * Note that a higher levelStep *reduces* the amount of memory needed for
	 * the hash table.
	 */
	levelStep = 1;
	for (;;)
	{
		double		subtreesize;
		double		maxlowestlevelpages;

		/* size of an average subtree at this levelStep (in pages). */
		subtreesize =
			(1 - pow(avgIndexTuplesPerPage, (double) (levelStep + 1))) /
			(1 - avgIndexTuplesPerPage);

		/* max number of pages at the lowest level of a subtree */
		maxlowestlevelpages = pow(maxIndexTuplesPerPage, (double) levelStep);

		/* subtree must fit in cache (with safety factor of 4) */
		if (subtreesize > effective_cache_size / 4)
			break;

		/* each node in the lowest level of a subtree has one page in memory */
		if (maxlowestlevelpages > ((double) maintenance_work_mem * 1024) / BLCKSZ)
			break;

		/* Good, we can handle this levelStep. See if we can go one higher. */
		levelStep++;
	}

	/*
	 * We just reached an unacceptable value of levelStep in previous loop.
	 * So, decrease levelStep to get last acceptable value.
	 */
	levelStep--;

	/*
	 * If there's not enough cache or maintenance_work_mem, fall back to plain
	 * inserts.
	 */
	if (levelStep <= 0)
	{
		elog(DEBUG1, "failed to switch to buffered GiST build");
		buildstate->bufferingMode = GIST_BUFFERING_DISABLED;
		return;
	}

	/*
	 * The second parameter to set is pagesPerBuffer, which determines the
	 * size of each buffer. We adjust pagesPerBuffer also during the build,
	 * which is why this calculation is in a separate function.
	 */
	pagesPerBuffer = calculatePagesPerBuffer(buildstate, levelStep);

	/* Initialize GISTBuildBuffers with these parameters */
	buildstate->gfbb = gistInitBuildBuffers(pagesPerBuffer, levelStep,
											gistGetMaxLevel(index));

	gistInitParentMap(buildstate);

	buildstate->bufferingMode = GIST_BUFFERING_ACTIVE;

	elog(DEBUG1, "switched to buffered GiST build; level step = %d, pagesPerBuffer = %d",
		 levelStep, pagesPerBuffer);
}