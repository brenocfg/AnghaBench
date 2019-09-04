#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  SupportAbility; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_BB_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_ANT_DIV ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void ODM_StopAntennaSwitchDm(PDM_ODM_T pDM_Odm)
{
	// disable ODM antenna diversity
	pDM_Odm->SupportAbility &= ~ODM_BB_ANT_DIV;
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_ANT_DIV,
		ODM_DBG_LOUD,
		("STOP Antenna Diversity\n")
	);
}