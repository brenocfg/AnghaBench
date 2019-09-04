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
struct TYPE_5__ {int* probe_timer_values; void* vbuson_timer; void* sense_timer; int /*<<< orphan*/  attached; scalar_t__ gpwrdn; scalar_t__ probe_counter; scalar_t__ vbuson_timer_started; scalar_t__ sense_timer_started; scalar_t__ sense_enabled; scalar_t__ probe_enabled; scalar_t__ initial_probe; scalar_t__ adp_started; } ;
struct TYPE_6__ {TYPE_1__ adp; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_OTG_ADP_UNKOWN ; 
 void* DWC_TIMER_ALLOC (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  adp_sense_timeout ; 
 int /*<<< orphan*/  adp_vbuson_timeout ; 

void dwc_otg_adp_init(dwc_otg_core_if_t * core_if)
{
	core_if->adp.adp_started = 0;
	core_if->adp.initial_probe = 0;
	core_if->adp.probe_timer_values[0] = -1;
	core_if->adp.probe_timer_values[1] = -1;
	core_if->adp.probe_enabled = 0;
	core_if->adp.sense_enabled = 0;
	core_if->adp.sense_timer_started = 0;
	core_if->adp.vbuson_timer_started = 0;
	core_if->adp.probe_counter = 0;
	core_if->adp.gpwrdn = 0;
	core_if->adp.attached = DWC_OTG_ADP_UNKOWN;
	/* Initialize timers */
	core_if->adp.sense_timer =
	    DWC_TIMER_ALLOC("ADP SENSE TIMER", adp_sense_timeout, core_if);
	core_if->adp.vbuson_timer =
	    DWC_TIMER_ALLOC("ADP VBUS ON TIMER", adp_vbuson_timeout, core_if);
	if (!core_if->adp.sense_timer || !core_if->adp.vbuson_timer)
	{
		DWC_ERROR("Could not allocate memory for ADP timers\n");
	}
}