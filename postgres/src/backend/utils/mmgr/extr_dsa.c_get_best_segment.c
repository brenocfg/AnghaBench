#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* header; int /*<<< orphan*/  fpm; } ;
typedef  TYPE_3__ dsa_segment_map ;
typedef  scalar_t__ dsa_segment_index ;
struct TYPE_16__ {TYPE_1__* control; } ;
typedef  TYPE_4__ dsa_area ;
struct TYPE_14__ {scalar_t__ next; size_t bin; scalar_t__ prev; } ;
struct TYPE_13__ {scalar_t__* segment_bins; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_4__*) ; 
 size_t DSA_NUM_SEGMENT_BINS ; 
 scalar_t__ DSA_SEGMENT_INDEX_NONE ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_freed_segments_locked (TYPE_4__*) ; 
 size_t contiguous_pages_to_segment_bin (size_t) ; 
 size_t fpm_largest (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_segment_by_index (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  unlink_segment (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static dsa_segment_map *
get_best_segment(dsa_area *area, size_t npages)
{
	size_t		bin;

	Assert(LWLockHeldByMe(DSA_AREA_LOCK(area)));
	check_for_freed_segments_locked(area);

	/*
	 * Start searching from the first bin that *might* have enough contiguous
	 * pages.
	 */
	for (bin = contiguous_pages_to_segment_bin(npages);
		 bin < DSA_NUM_SEGMENT_BINS;
		 ++bin)
	{
		/*
		 * The minimum contiguous size that any segment in this bin should
		 * have.  We'll re-bin if we see segments with fewer.
		 */
		size_t		threshold = (size_t) 1 << (bin - 1);
		dsa_segment_index segment_index;

		/* Search this bin for a segment with enough contiguous space. */
		segment_index = area->control->segment_bins[bin];
		while (segment_index != DSA_SEGMENT_INDEX_NONE)
		{
			dsa_segment_map *segment_map;
			dsa_segment_index next_segment_index;
			size_t		contiguous_pages;

			segment_map = get_segment_by_index(area, segment_index);
			next_segment_index = segment_map->header->next;
			contiguous_pages = fpm_largest(segment_map->fpm);

			/* Not enough for the request, still enough for this bin. */
			if (contiguous_pages >= threshold && contiguous_pages < npages)
			{
				segment_index = next_segment_index;
				continue;
			}

			/* Re-bin it if it's no longer in the appropriate bin. */
			if (contiguous_pages < threshold)
			{
				size_t		new_bin;

				new_bin = contiguous_pages_to_segment_bin(contiguous_pages);

				/* Remove it from its current bin. */
				unlink_segment(area, segment_map);

				/* Push it onto the front of its new bin. */
				segment_map->header->prev = DSA_SEGMENT_INDEX_NONE;
				segment_map->header->next =
					area->control->segment_bins[new_bin];
				segment_map->header->bin = new_bin;
				area->control->segment_bins[new_bin] = segment_index;
				if (segment_map->header->next != DSA_SEGMENT_INDEX_NONE)
				{
					dsa_segment_map *next;

					next = get_segment_by_index(area,
												segment_map->header->next);
					Assert(next->header->bin == new_bin);
					next->header->prev = segment_index;
				}

				/*
				 * But fall through to see if it's enough to satisfy this
				 * request anyway....
				 */
			}

			/* Check if we are done. */
			if (contiguous_pages >= npages)
				return segment_map;

			/* Continue searching the same bin. */
			segment_index = next_segment_index;
		}
	}

	/* Not found. */
	return NULL;
}