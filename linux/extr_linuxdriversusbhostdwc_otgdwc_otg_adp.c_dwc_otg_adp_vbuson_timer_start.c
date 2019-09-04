#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vbuson_timer_started; scalar_t__ vbuson_timer; } ;
struct TYPE_5__ {TYPE_1__ adp; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_TIMER_SCHEDULE (scalar_t__,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*,scalar_t__) ; 

void dwc_otg_adp_vbuson_timer_start(dwc_otg_core_if_t * core_if)
{
	core_if->adp.vbuson_timer_started = 1;
	if (core_if->adp.vbuson_timer)
	{
		DWC_PRINTF("SCHEDULING VBUSON TIMER\n");
		/* 1.1 secs + 60ms necessary for cil_hcd_start*/
		DWC_TIMER_SCHEDULE(core_if->adp.vbuson_timer, 1160);
	} else {
		DWC_WARN("VBUSON_TIMER = %p\n",core_if->adp.vbuson_timer);
	}
}