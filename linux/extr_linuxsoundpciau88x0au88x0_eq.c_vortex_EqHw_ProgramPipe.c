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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  asEqCoefsPipes ; 
 int /*<<< orphan*/  eq_gains_current ; 
 int /*<<< orphan*/  vortex_EqHw_SetLeftCoefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightCoefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightGainsCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightGainsTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetTimeConsts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_EqHw_ProgramPipe(vortex_t * vortex)
{
	vortex_EqHw_SetTimeConsts(vortex, 0, 0);

	vortex_EqHw_SetLeftCoefs(vortex, asEqCoefsPipes);
	vortex_EqHw_SetRightCoefs(vortex, asEqCoefsPipes);

	vortex_EqHw_SetLeftGainsCurrent(vortex, eq_gains_current);
	vortex_EqHw_SetRightGainsCurrent(vortex, eq_gains_current);
	vortex_EqHw_SetLeftGainsTarget(vortex, eq_gains_current);
	vortex_EqHw_SetRightGainsTarget(vortex, eq_gains_current);
}