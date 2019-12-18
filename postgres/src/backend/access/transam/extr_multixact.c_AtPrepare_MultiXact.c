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
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 scalar_t__ MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 size_t MyBackendId ; 
 int /*<<< orphan*/ * OldestMemberMXactId ; 
 int /*<<< orphan*/  RegisterTwoPhaseRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TWOPHASE_RM_MULTIXACT_ID ; 

void
AtPrepare_MultiXact(void)
{
	MultiXactId myOldestMember = OldestMemberMXactId[MyBackendId];

	if (MultiXactIdIsValid(myOldestMember))
		RegisterTwoPhaseRecord(TWOPHASE_RM_MULTIXACT_ID, 0,
							   &myOldestMember, sizeof(MultiXactId));
}