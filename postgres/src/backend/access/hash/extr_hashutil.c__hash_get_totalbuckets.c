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
typedef  int uint32 ;

/* Variables and functions */
 int HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE ; 
 int HASH_SPLITPOINT_PHASE_BITS ; 
 int HASH_SPLITPOINT_PHASE_MASK ; 

uint32
_hash_get_totalbuckets(uint32 splitpoint_phase)
{
	uint32		splitpoint_group;
	uint32		total_buckets;
	uint32		phases_within_splitpoint_group;

	if (splitpoint_phase < HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE)
		return (1 << splitpoint_phase);

	/* get splitpoint's group */
	splitpoint_group = HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE;
	splitpoint_group +=
		((splitpoint_phase - HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE) >>
		 HASH_SPLITPOINT_PHASE_BITS);

	/* account for buckets before splitpoint_group */
	total_buckets = (1 << (splitpoint_group - 1));

	/* account for buckets within splitpoint_group */
	phases_within_splitpoint_group =
		(((splitpoint_phase - HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE) &
		  HASH_SPLITPOINT_PHASE_MASK) + 1); /* from 0-based to 1-based */
	total_buckets +=
		(((1 << (splitpoint_group - 1)) >> HASH_SPLITPOINT_PHASE_BITS) *
		 phases_within_splitpoint_group);

	return total_buckets;
}