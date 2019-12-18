#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/ * mapped_address; TYPE_2__* header; int /*<<< orphan*/ * segment; int /*<<< orphan*/  fpm; } ;
typedef  TYPE_3__ dsa_segment_map ;
typedef  size_t dsa_segment_index ;
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_23__ {int size_class; int /*<<< orphan*/  npages; int /*<<< orphan*/  start; } ;
typedef  TYPE_4__ dsa_area_span ;
struct TYPE_24__ {TYPE_1__* control; } ;
typedef  TYPE_5__ dsa_area ;
struct TYPE_21__ {scalar_t__ usable_pages; int freed; scalar_t__ size; } ;
struct TYPE_20__ {scalar_t__ total_segment_size; int /*<<< orphan*/  freed_segment_counter; int /*<<< orphan*/ * segment_handles; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_5__*) ; 
 int DSA_EXTRACT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_EXTRACT_SEGMENT_NUMBER (int /*<<< orphan*/ ) ; 
 int DSA_SCLASS_BLOCK_OF_SPANS ; 
 int /*<<< orphan*/  DSM_HANDLE_INVALID ; 
 int FPM_PAGE_SIZE ; 
 int /*<<< orphan*/  FreePageManagerPut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  check_for_freed_segments_locked (TYPE_5__*) ; 
 int /*<<< orphan*/  dsa_free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* dsa_get_address (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_unpin_segment (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_largest (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_segment_by_index (TYPE_5__*,int /*<<< orphan*/ ) ; 
 size_t get_segment_index (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  unlink_segment (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  unlink_span (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static void
destroy_superblock(dsa_area *area, dsa_pointer span_pointer)
{
	dsa_area_span *span = dsa_get_address(area, span_pointer);
	int			size_class = span->size_class;
	dsa_segment_map *segment_map;


	/* Remove it from its fullness class list. */
	unlink_span(area, span);

	/*
	 * Note: Here we acquire the area lock while we already hold a per-pool
	 * lock.  We never hold the area lock and then take a pool lock, or we
	 * could deadlock.
	 */
	LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);
	check_for_freed_segments_locked(area);
	segment_map =
		get_segment_by_index(area, DSA_EXTRACT_SEGMENT_NUMBER(span->start));
	FreePageManagerPut(segment_map->fpm,
					   DSA_EXTRACT_OFFSET(span->start) / FPM_PAGE_SIZE,
					   span->npages);
	/* Check if the segment is now entirely free. */
	if (fpm_largest(segment_map->fpm) == segment_map->header->usable_pages)
	{
		dsa_segment_index index = get_segment_index(area, segment_map);

		/* If it's not the segment with extra control data, free it. */
		if (index != 0)
		{
			/*
			 * Give it back to the OS, and allow other backends to detect that
			 * they need to detach.
			 */
			unlink_segment(area, segment_map);
			segment_map->header->freed = true;
			Assert(area->control->total_segment_size >=
				   segment_map->header->size);
			area->control->total_segment_size -=
				segment_map->header->size;
			dsm_unpin_segment(dsm_segment_handle(segment_map->segment));
			dsm_detach(segment_map->segment);
			area->control->segment_handles[index] = DSM_HANDLE_INVALID;
			++area->control->freed_segment_counter;
			segment_map->segment = NULL;
			segment_map->header = NULL;
			segment_map->mapped_address = NULL;
		}
	}
	LWLockRelease(DSA_AREA_LOCK(area));

	/*
	 * Span-of-spans blocks store the span which describes them within the
	 * block itself, so freeing the storage implicitly frees the descriptor
	 * also.  If this is a block of any other type, we need to separately free
	 * the span object also.  This recursive call to dsa_free will acquire the
	 * span pool's lock.  We can't deadlock because the acquisition order is
	 * always some other pool and then the span pool.
	 */
	if (size_class != DSA_SCLASS_BLOCK_OF_SPANS)
		dsa_free(area, span_pointer);
}