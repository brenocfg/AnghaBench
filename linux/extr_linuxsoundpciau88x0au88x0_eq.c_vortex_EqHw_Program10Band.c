#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vortex_t ;
struct TYPE_3__ {int /*<<< orphan*/  RightGains; int /*<<< orphan*/  LeftGains; int /*<<< orphan*/  RightCoefs; int /*<<< orphan*/  LeftCoefs; } ;
typedef  TYPE_1__ auxxEqCoeffSet_t ;

/* Variables and functions */
 int /*<<< orphan*/  vortex_EqHw_SetLeftCoefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightCoefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightGainsCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightGainsTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_EqHw_SetTimeConsts (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
vortex_EqHw_Program10Band(vortex_t * vortex, auxxEqCoeffSet_t * coefset)
{

	vortex_EqHw_SetTimeConsts(vortex, 0xc, 0x7fe0);

	vortex_EqHw_SetLeftCoefs(vortex, coefset->LeftCoefs);
	vortex_EqHw_SetRightCoefs(vortex, coefset->RightCoefs);

	vortex_EqHw_SetLeftGainsCurrent(vortex, coefset->LeftGains);

	vortex_EqHw_SetRightGainsTarget(vortex, coefset->RightGains);
	vortex_EqHw_SetLeftGainsTarget(vortex, coefset->LeftGains);

	vortex_EqHw_SetRightGainsCurrent(vortex, coefset->RightGains);
}