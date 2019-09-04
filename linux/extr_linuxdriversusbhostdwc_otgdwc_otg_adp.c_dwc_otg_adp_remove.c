#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int pmuintsel; int pmuactv; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_4__ gpwrdn_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  vbuson_timer; int /*<<< orphan*/  sense_timer; scalar_t__ vbuson_timer_started; scalar_t__ sense_timer_started; scalar_t__ sense_enabled; scalar_t__ probe_enabled; } ;
struct TYPE_13__ {TYPE_3__ adp; TYPE_2__* core_global_regs; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_10__ {int /*<<< orphan*/  gpwrdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_CANCEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_stop (TYPE_5__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_sense_stop (TYPE_5__*) ; 

void dwc_otg_adp_remove(dwc_otg_core_if_t * core_if)
{
	gpwrdn_data_t gpwrdn = { .d32 = 0 };
	gpwrdn.b.pmuintsel = 1;
	gpwrdn.b.pmuactv = 1;
	DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, gpwrdn.d32, 0);

	if (core_if->adp.probe_enabled)
		dwc_otg_adp_probe_stop(core_if);
	if (core_if->adp.sense_enabled)
		dwc_otg_adp_sense_stop(core_if);
	if (core_if->adp.sense_timer_started)
		DWC_TIMER_CANCEL(core_if->adp.sense_timer);
	if (core_if->adp.vbuson_timer_started)
		DWC_TIMER_CANCEL(core_if->adp.vbuson_timer);
	DWC_TIMER_FREE(core_if->adp.sense_timer);
	DWC_TIMER_FREE(core_if->adp.vbuson_timer);
}