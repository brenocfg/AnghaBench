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
typedef  scalar_t__ TimeLineID ;
typedef  scalar_t__ RecoveryTargetTimeLineGoal ;

/* Variables and functions */
 scalar_t__ RECOVERY_TARGET_TIMELINE_NUMERIC ; 
 scalar_t__ recoveryTargetTLIRequested ; 
 scalar_t__ recoveryTargetTimeLineGoal ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assign_recovery_target_timeline(const char *newval, void *extra)
{
	recoveryTargetTimeLineGoal = *((RecoveryTargetTimeLineGoal *) extra);
	if (recoveryTargetTimeLineGoal == RECOVERY_TARGET_TIMELINE_NUMERIC)
		recoveryTargetTLIRequested = (TimeLineID) strtoul(newval, NULL, 0);
	else
		recoveryTargetTLIRequested = 0;
}