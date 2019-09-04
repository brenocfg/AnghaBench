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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;
struct TYPE_3__ {int adp_sns_int; int adp_sns_int_msk; int adp_tmout_int; int adp_tmout_int_msk; int adp_prb_int; int adp_prb_int_msk; } ;
struct TYPE_4__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_2__ adpctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 int dwc_otg_adp_handle_prb_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_adp_handle_prb_tmout_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_adp_handle_sns_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_adp_read_reg (int /*<<< orphan*/ *) ; 

int32_t dwc_otg_adp_handle_intr(dwc_otg_core_if_t * core_if)
{
	int retval = 0;
	adpctl_data_t adpctl = {.d32 = 0};

	adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	DWC_PRINTF("ADPCTL = %08x\n",adpctl.d32);

	if (adpctl.b.adp_sns_int & adpctl.b.adp_sns_int_msk) {
		DWC_PRINTF("ADP Sense interrupt\n");
		retval |= dwc_otg_adp_handle_sns_intr(core_if);
	}
	if (adpctl.b.adp_tmout_int & adpctl.b.adp_tmout_int_msk) {
		DWC_PRINTF("ADP timeout interrupt\n");
		retval |= dwc_otg_adp_handle_prb_tmout_intr(core_if, adpctl.d32);
	}
	if (adpctl.b.adp_prb_int & adpctl.b.adp_prb_int_msk) {
		DWC_PRINTF("ADP Probe interrupt\n");
		adpctl.b.adp_prb_int = 1;
		retval |= dwc_otg_adp_handle_prb_intr(core_if, adpctl.d32);
	}

//	dwc_otg_adp_modify_reg(core_if, adpctl.d32, 0);
	//dwc_otg_adp_write_reg(core_if, adpctl.d32);
	DWC_PRINTF("RETURN FROM ADP ISR\n");

	return retval;
}