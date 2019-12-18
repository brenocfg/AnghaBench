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
 int /*<<< orphan*/  DSM_HANDLE_INVALID ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 int /*<<< orphan*/ * attach_internal (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_on_dsm_detach_release_in_place ; 
 int /*<<< orphan*/  on_dsm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

dsa_area *
dsa_attach_in_place(void *place, dsm_segment *segment)
{
	dsa_area   *area;

	area = attach_internal(place, NULL, DSM_HANDLE_INVALID);

	/*
	 * Clean up when the control segment detaches, if a containing DSM segment
	 * was provided.
	 */
	if (segment != NULL)
		on_dsm_detach(segment, &dsa_on_dsm_detach_release_in_place,
					  PointerGetDatum(place));

	return area;
}