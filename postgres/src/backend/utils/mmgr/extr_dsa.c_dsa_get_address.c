#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t dsa_segment_index ;
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_7__ {TYPE_1__* segment_maps; } ;
typedef  TYPE_2__ dsa_area ;
struct TYPE_6__ {void* mapped_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t DSA_EXTRACT_OFFSET (int /*<<< orphan*/ ) ; 
 size_t DSA_EXTRACT_SEGMENT_NUMBER (int /*<<< orphan*/ ) ; 
 size_t DSA_MAX_SEGMENTS ; 
 int /*<<< orphan*/  DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_freed_segments (TYPE_2__*) ; 
 int /*<<< orphan*/  get_segment_by_index (TYPE_2__*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void *
dsa_get_address(dsa_area *area, dsa_pointer dp)
{
	dsa_segment_index index;
	size_t		offset;

	/* Convert InvalidDsaPointer to NULL. */
	if (!DsaPointerIsValid(dp))
		return NULL;

	/* Process any requests to detach from freed segments. */
	check_for_freed_segments(area);

	/* Break the dsa_pointer into its components. */
	index = DSA_EXTRACT_SEGMENT_NUMBER(dp);
	offset = DSA_EXTRACT_OFFSET(dp);
	Assert(index < DSA_MAX_SEGMENTS);

	/* Check if we need to cause this segment to be mapped in. */
	if (unlikely(area->segment_maps[index].mapped_address == NULL))
	{
		/* Call for effect (we don't need the result). */
		get_segment_by_index(area, index);
	}

	return area->segment_maps[index].mapped_address + offset;
}