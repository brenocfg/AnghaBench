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
struct TYPE_7__ {size_t this10; int /*<<< orphan*/ * this130; } ;
struct TYPE_6__ {TYPE_2__ eq; } ;
typedef  TYPE_1__ vortex_t ;
typedef  TYPE_2__ eqlzr_t ;

/* Variables and functions */
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsTarget (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_EqHw_SetRightGainsTarget (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vortex_Eqlzr_SetAllBandsFromActiveCoeffSet(vortex_t * vortex)
{
	eqlzr_t *eq = &(vortex->eq);

	vortex_EqHw_SetLeftGainsTarget(vortex, eq->this130);
	vortex_EqHw_SetRightGainsTarget(vortex, &(eq->this130[eq->this10]));

	return 0;
}