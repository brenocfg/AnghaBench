#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ this28; size_t* this130; scalar_t__ this54; } ;
struct TYPE_5__ {TYPE_2__ eq; } ;
typedef  TYPE_1__ vortex_t ;
typedef  size_t u16 ;
typedef  TYPE_2__ eqlzr_t ;

/* Variables and functions */
 int /*<<< orphan*/  vortex_EqHw_SetLeftGainsSingleTarget (TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void vortex_Eqlzr_SetLeftGain(vortex_t * vortex, u16 index, u16 gain)
{
	eqlzr_t *eq = &(vortex->eq);

	if (eq->this28 == 0)
		return;

	eq->this130[index] = gain;
	if (eq->this54)
		return;

	vortex_EqHw_SetLeftGainsSingleTarget(vortex, index, gain);
}