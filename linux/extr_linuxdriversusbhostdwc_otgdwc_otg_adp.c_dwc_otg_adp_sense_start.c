#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;
struct TYPE_3__ {int adp_sns_int_msk; int adpres; int adpen; int enasns; } ;
struct TYPE_4__ {void* d32; TYPE_1__ b; } ;
typedef  TYPE_2__ adpctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 void* dwc_otg_adp_read_reg (int /*<<< orphan*/ *) ; 
 void* dwc_otg_adp_read_reg_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_adp_sense_timer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dwc_otg_disable_global_interrupts (int /*<<< orphan*/ *) ; 

uint32_t dwc_otg_adp_sense_start(dwc_otg_core_if_t * core_if)
{
	adpctl_data_t adpctl;

	DWC_PRINTF("ADP Sense Start\n");

	/* Unmask ADP sense interrupt and mask all other from the core */
	adpctl.d32 = dwc_otg_adp_read_reg_filter(core_if);
	adpctl.b.adp_sns_int_msk = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);
	dwc_otg_disable_global_interrupts(core_if); // vahrama

	/* Set ADP reset bit*/
	adpctl.d32 = dwc_otg_adp_read_reg_filter(core_if);
	adpctl.b.adpres = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	while (adpctl.b.adpres) {
		adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	}

	adpctl.b.adpres = 0;
	adpctl.b.adpen = 1;
	adpctl.b.enasns = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	dwc_otg_adp_sense_timer_start(core_if);

	return 0;
}