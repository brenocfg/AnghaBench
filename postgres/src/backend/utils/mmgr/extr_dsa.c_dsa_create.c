#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsa_area ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_INITIAL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_on_dsm_detach_release_in_place ; 
 int /*<<< orphan*/ * dsm_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_pin_segment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_dsm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

dsa_area *
dsa_create(int tranche_id)
{
	dsm_segment *segment;
	dsa_area   *area;

	/*
	 * Create the DSM segment that will hold the shared control object and the
	 * first segment of usable space.
	 */
	segment = dsm_create(DSA_INITIAL_SEGMENT_SIZE, 0);

	/*
	 * All segments backing this area are pinned, so that DSA can explicitly
	 * control their lifetime (otherwise a newly created segment belonging to
	 * this area might be freed when the only backend that happens to have it
	 * mapped in ends, corrupting the area).
	 */
	dsm_pin_segment(segment);

	/* Create a new DSA area with the control object in this segment. */
	area = create_internal(dsm_segment_address(segment),
						   DSA_INITIAL_SEGMENT_SIZE,
						   tranche_id,
						   dsm_segment_handle(segment), segment);

	/* Clean up when the control segment detaches. */
	on_dsm_detach(segment, &dsa_on_dsm_detach_release_in_place,
				  PointerGetDatum(dsm_segment_address(segment)));

	return area;
}