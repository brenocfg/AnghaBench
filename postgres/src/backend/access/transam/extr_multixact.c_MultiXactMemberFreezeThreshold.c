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
typedef  double uint32 ;
typedef  scalar_t__ MultiXactOffset ;

/* Variables and functions */
 scalar_t__ MULTIXACT_MEMBER_DANGER_THRESHOLD ; 
 scalar_t__ MULTIXACT_MEMBER_SAFE_THRESHOLD ; 
 int /*<<< orphan*/  ReadMultiXactCounts (double*,scalar_t__*) ; 
 int autovacuum_multixact_freeze_max_age ; 

int
MultiXactMemberFreezeThreshold(void)
{
	MultiXactOffset members;
	uint32		multixacts;
	uint32		victim_multixacts;
	double		fraction;

	/* If we can't determine member space utilization, assume the worst. */
	if (!ReadMultiXactCounts(&multixacts, &members))
		return 0;

	/* If member space utilization is low, no special action is required. */
	if (members <= MULTIXACT_MEMBER_SAFE_THRESHOLD)
		return autovacuum_multixact_freeze_max_age;

	/*
	 * Compute a target for relminmxid advancement.  The number of multixacts
	 * we try to eliminate from the system is based on how far we are past
	 * MULTIXACT_MEMBER_SAFE_THRESHOLD.
	 */
	fraction = (double) (members - MULTIXACT_MEMBER_SAFE_THRESHOLD) /
		(MULTIXACT_MEMBER_DANGER_THRESHOLD - MULTIXACT_MEMBER_SAFE_THRESHOLD);
	victim_multixacts = multixacts * fraction;

	/* fraction could be > 1.0, but lowest possible freeze age is zero */
	if (victim_multixacts > multixacts)
		return 0;
	return multixacts - victim_multixacts;
}