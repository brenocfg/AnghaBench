#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  sense_timer; } ;
struct TYPE_11__ {TYPE_1__ adp; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_10__ {int adp_sns_int; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_4__ adpctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_TIMER_CANCEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_adp_read_reg (TYPE_3__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_sense_timer_start (TYPE_3__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t dwc_otg_adp_handle_sns_intr(dwc_otg_core_if_t * core_if)
{
	adpctl_data_t adpctl;
	/* Stop ADP Sense timer */
	DWC_TIMER_CANCEL(core_if->adp.sense_timer);

	/* Restart ADP Sense timer */
	dwc_otg_adp_sense_timer_start(core_if);

	/* Clear interrupt */
	adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	adpctl.b.adp_sns_int = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	return 0;
}