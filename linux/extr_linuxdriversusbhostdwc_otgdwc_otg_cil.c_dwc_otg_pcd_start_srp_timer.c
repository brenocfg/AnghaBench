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
struct TYPE_3__ {int srp_timer_started; int /*<<< orphan*/  srp_timer; } ;
typedef  TYPE_1__ dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_TIMER_SCHEDULE (int /*<<< orphan*/ ,int) ; 

void dwc_otg_pcd_start_srp_timer(dwc_otg_core_if_t * core_if)
{
	core_if->srp_timer_started = 1;
	DWC_TIMER_SCHEDULE(core_if->srp_timer, 6000 /* 6 secs */ );
}