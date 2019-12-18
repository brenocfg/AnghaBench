#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* header; } ;
typedef  TYPE_3__ dsa_segment_map ;
struct TYPE_14__ {TYPE_1__* control; } ;
typedef  TYPE_4__ dsa_area ;
struct TYPE_12__ {scalar_t__ prev; scalar_t__ next; size_t bin; } ;
struct TYPE_11__ {scalar_t__* segment_bins; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSA_SEGMENT_INDEX_NONE ; 
 TYPE_3__* get_segment_by_index (TYPE_4__*,scalar_t__) ; 
 scalar_t__ get_segment_index (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void
unlink_segment(dsa_area *area, dsa_segment_map *segment_map)
{
	if (segment_map->header->prev != DSA_SEGMENT_INDEX_NONE)
	{
		dsa_segment_map *prev;

		prev = get_segment_by_index(area, segment_map->header->prev);
		prev->header->next = segment_map->header->next;
	}
	else
	{
		Assert(area->control->segment_bins[segment_map->header->bin] ==
			   get_segment_index(area, segment_map));
		area->control->segment_bins[segment_map->header->bin] =
			segment_map->header->next;
	}
	if (segment_map->header->next != DSA_SEGMENT_INDEX_NONE)
	{
		dsa_segment_map *next;

		next = get_segment_by_index(area, segment_map->header->next);
		next->header->prev = segment_map->header->prev;
	}
}