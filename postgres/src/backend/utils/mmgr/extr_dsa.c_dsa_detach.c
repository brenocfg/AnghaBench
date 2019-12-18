#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int high_segment_index; TYPE_1__* segment_maps; } ;
typedef  TYPE_2__ dsa_area ;
struct TYPE_5__ {int /*<<< orphan*/ * segment; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

void
dsa_detach(dsa_area *area)
{
	int			i;

	/* Detach from all segments. */
	for (i = 0; i <= area->high_segment_index; ++i)
		if (area->segment_maps[i].segment != NULL)
			dsm_detach(area->segment_maps[i].segment);

	/*
	 * Note that 'detaching' (= detaching from DSM segments) doesn't include
	 * 'releasing' (= adjusting the reference count).  It would be nice to
	 * combine these operations, but client code might never get around to
	 * calling dsa_detach because of an error path, and a detach hook on any
	 * particular segment is too late to detach other segments in the area
	 * without risking a 'leak' warning in the non-error path.
	 */

	/* Free the backend-local area object. */
	pfree(area);
}