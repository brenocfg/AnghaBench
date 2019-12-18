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
struct TYPE_10__ {void** pagemap; int /*<<< orphan*/  fpm; } ;
typedef  TYPE_1__ dsa_segment_map ;
typedef  void* dsa_pointer ;
struct TYPE_11__ {void* nextspan; size_t nallocatable; void* prevspan; int fclass; } ;
typedef  TYPE_2__ dsa_area_span ;
struct TYPE_12__ {void** spans; } ;
typedef  TYPE_3__ dsa_area_pool ;
typedef  int /*<<< orphan*/  dsa_area ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DSA_AREA_LOCK (int /*<<< orphan*/ *) ; 
 int DSA_FULLNESS_CLASSES ; 
 void* DSA_MAKE_POINTER (int /*<<< orphan*/ ,size_t) ; 
 size_t DSA_PAGES_PER_SUPERBLOCK ; 
 int DSA_SCLASS_BLOCK_OF_SPANS ; 
 int /*<<< orphan*/  DSA_SCLASS_LOCK (int /*<<< orphan*/ *,int) ; 
 size_t DSA_SUPERBLOCK_SIZE ; 
 int DsaPointerIsValid (void*) ; 
 int /*<<< orphan*/  FATAL ; 
 size_t FPM_PAGE_SIZE ; 
 int /*<<< orphan*/  FreePageManagerGet (int /*<<< orphan*/ ,size_t,size_t*) ; 
 void* InvalidDsaPointer ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 void* alloc_object (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ *,void*) ; 
 size_t* dsa_size_classes ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_1__* get_best_segment (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  get_segment_index (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_span (int /*<<< orphan*/ *,void*,TYPE_3__*,void*,size_t,int) ; 
 TYPE_1__* make_new_segment (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ transfer_first_span (int /*<<< orphan*/ *,TYPE_3__*,int,int) ; 

__attribute__((used)) static bool
ensure_active_superblock(dsa_area *area, dsa_area_pool *pool,
						 int size_class)
{
	dsa_pointer span_pointer;
	dsa_pointer start_pointer;
	size_t		obsize = dsa_size_classes[size_class];
	size_t		nmax;
	int			fclass;
	size_t		npages = 1;
	size_t		first_page;
	size_t		i;
	dsa_segment_map *segment_map;

	Assert(LWLockHeldByMe(DSA_SCLASS_LOCK(area, size_class)));

	/*
	 * Compute the number of objects that will fit in a block of this size
	 * class.  Span-of-spans blocks are just a single page, and the first
	 * object isn't available for use because it describes the block-of-spans
	 * itself.
	 */
	if (size_class == DSA_SCLASS_BLOCK_OF_SPANS)
		nmax = FPM_PAGE_SIZE / obsize - 1;
	else
		nmax = DSA_SUPERBLOCK_SIZE / obsize;

	/*
	 * If fullness class 1 is empty, try to find a span to put in it by
	 * scanning higher-numbered fullness classes (excluding the last one,
	 * whose blocks are certain to all be completely full).
	 */
	for (fclass = 2; fclass < DSA_FULLNESS_CLASSES - 1; ++fclass)
	{
		span_pointer = pool->spans[fclass];

		while (DsaPointerIsValid(span_pointer))
		{
			int			tfclass;
			dsa_area_span *span;
			dsa_area_span *nextspan;
			dsa_area_span *prevspan;
			dsa_pointer next_span_pointer;

			span = (dsa_area_span *)
				dsa_get_address(area, span_pointer);
			next_span_pointer = span->nextspan;

			/* Figure out what fullness class should contain this span. */
			tfclass = (nmax - span->nallocatable)
				* (DSA_FULLNESS_CLASSES - 1) / nmax;

			/* Look up next span. */
			if (DsaPointerIsValid(span->nextspan))
				nextspan = (dsa_area_span *)
					dsa_get_address(area, span->nextspan);
			else
				nextspan = NULL;

			/*
			 * If utilization has dropped enough that this now belongs in some
			 * other fullness class, move it there.
			 */
			if (tfclass < fclass)
			{
				/* Remove from the current fullness class list. */
				if (pool->spans[fclass] == span_pointer)
				{
					/* It was the head; remove it. */
					Assert(!DsaPointerIsValid(span->prevspan));
					pool->spans[fclass] = span->nextspan;
					if (nextspan != NULL)
						nextspan->prevspan = InvalidDsaPointer;
				}
				else
				{
					/* It was not the head. */
					Assert(DsaPointerIsValid(span->prevspan));
					prevspan = (dsa_area_span *)
						dsa_get_address(area, span->prevspan);
					prevspan->nextspan = span->nextspan;
				}
				if (nextspan != NULL)
					nextspan->prevspan = span->prevspan;

				/* Push onto the head of the new fullness class list. */
				span->nextspan = pool->spans[tfclass];
				pool->spans[tfclass] = span_pointer;
				span->prevspan = InvalidDsaPointer;
				if (DsaPointerIsValid(span->nextspan))
				{
					nextspan = (dsa_area_span *)
						dsa_get_address(area, span->nextspan);
					nextspan->prevspan = span_pointer;
				}
				span->fclass = tfclass;
			}

			/* Advance to next span on list. */
			span_pointer = next_span_pointer;
		}

		/* Stop now if we found a suitable block. */
		if (DsaPointerIsValid(pool->spans[1]))
			return true;
	}

	/*
	 * If there are no blocks that properly belong in fullness class 1, pick
	 * one from some other fullness class and move it there anyway, so that we
	 * have an allocation target.  Our last choice is to transfer a block
	 * that's almost empty (and might become completely empty soon if left
	 * alone), but even that is better than failing, which is what we must do
	 * if there are no blocks at all with freespace.
	 */
	Assert(!DsaPointerIsValid(pool->spans[1]));
	for (fclass = 2; fclass < DSA_FULLNESS_CLASSES - 1; ++fclass)
		if (transfer_first_span(area, pool, fclass, 1))
			return true;
	if (!DsaPointerIsValid(pool->spans[1]) &&
		transfer_first_span(area, pool, 0, 1))
		return true;

	/*
	 * We failed to find an existing span with free objects, so we need to
	 * allocate a new superblock and construct a new span to manage it.
	 *
	 * First, get a dsa_area_span object to describe the new superblock block
	 * ... unless this allocation is for a dsa_area_span object, in which case
	 * that's surely not going to work.  We handle that case by storing the
	 * span describing a block-of-spans inline.
	 */
	if (size_class != DSA_SCLASS_BLOCK_OF_SPANS)
	{
		span_pointer = alloc_object(area, DSA_SCLASS_BLOCK_OF_SPANS);
		if (!DsaPointerIsValid(span_pointer))
			return false;
		npages = DSA_PAGES_PER_SUPERBLOCK;
	}

	/* Find or create a segment and allocate the superblock. */
	LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);
	segment_map = get_best_segment(area, npages);
	if (segment_map == NULL)
	{
		segment_map = make_new_segment(area, npages);
		if (segment_map == NULL)
		{
			LWLockRelease(DSA_AREA_LOCK(area));
			return false;
		}
	}

	/*
	 * This shouldn't happen: get_best_segment() or make_new_segment()
	 * promised that we can successfully allocate npages.
	 */
	if (!FreePageManagerGet(segment_map->fpm, npages, &first_page))
		elog(FATAL,
			 "dsa_allocate could not find %zu free pages for superblock",
			 npages);
	LWLockRelease(DSA_AREA_LOCK(area));

	/* Compute the start of the superblock. */
	start_pointer =
		DSA_MAKE_POINTER(get_segment_index(area, segment_map),
						 first_page * FPM_PAGE_SIZE);

	/*
	 * If this is a block-of-spans, carve the descriptor right out of the
	 * allocated space.
	 */
	if (size_class == DSA_SCLASS_BLOCK_OF_SPANS)
	{
		/*
		 * We have a pointer into the segment.  We need to build a dsa_pointer
		 * from the segment index and offset into the segment.
		 */
		span_pointer = start_pointer;
	}

	/* Initialize span and pagemap. */
	init_span(area, span_pointer, pool, start_pointer, npages, size_class);
	for (i = 0; i < npages; ++i)
		segment_map->pagemap[first_page + i] = span_pointer;

	return true;
}