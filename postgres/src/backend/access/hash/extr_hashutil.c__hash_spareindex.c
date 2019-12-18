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
 int _hash_log2 (int) ; 

uint32
_hash_spareindex(uint32 num_bucket)
{
	uint32		splitpoint_group;
	uint32		splitpoint_phases;

	splitpoint_group = _hash_log2(num_bucket);

	if (splitpoint_group < HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE)
		return splitpoint_group;

	/* account for single-phase groups */
	splitpoint_phases = HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE;

	/* account for multi-phase groups before splitpoint_group */
	splitpoint_phases +=
		((splitpoint_group - HASH_SPLITPOINT_GROUPS_WITH_ONE_PHASE) <<
		 HASH_SPLITPOINT_PHASE_BITS);

	/* account for phases within current group */
	splitpoint_phases +=
		(((num_bucket - 1) >>
		  (splitpoint_group - (HASH_SPLITPOINT_PHASE_BITS + 1))) &
		 HASH_SPLITPOINT_PHASE_MASK);	/* to 0-based value. */

	return splitpoint_phases;
}