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
struct TYPE_5__ {scalar_t__ sense_timer_started; } ;
struct TYPE_6__ {scalar_t__ adp_enable; TYPE_1__ adp; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_start (TYPE_2__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_sense_stop (TYPE_2__*) ; 

__attribute__((used)) static void adp_sense_timeout(void *ptr)
{
	dwc_otg_core_if_t *core_if = (dwc_otg_core_if_t *) ptr;
	core_if->adp.sense_timer_started = 0;
	DWC_PRINTF("ADP SENSE TIMEOUT\n");
	if (core_if->adp_enable) {
		dwc_otg_adp_sense_stop(core_if);
		dwc_otg_adp_probe_start(core_if);
	}
}