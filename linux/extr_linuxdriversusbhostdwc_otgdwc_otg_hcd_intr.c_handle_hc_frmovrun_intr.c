#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_11__ {TYPE_1__* urb; } ;
typedef  TYPE_2__ dwc_otg_qtd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_12__ {int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_3__ dwc_hc_t ;
struct TYPE_10__ {int /*<<< orphan*/  pipe_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_FRAME_OVERRUN ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frmovrun ; 
 int /*<<< orphan*/  halt_channel (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_isoc_urb_state (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_frmovrun_intr(dwc_otg_hcd_t * hcd,
				       dwc_hc_t * hc,
				       dwc_otg_hc_regs_t * hc_regs,
				       dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "Frame Overrun--\n", hc->hc_num);

	switch (dwc_otg_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
	case UE_CONTROL:
	case UE_BULK:
		break;
	case UE_INTERRUPT:
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_FRAME_OVERRUN);
		break;
	case UE_ISOCHRONOUS:
		{
			dwc_otg_halt_status_e halt_status;
			halt_status =
			    update_isoc_urb_state(hcd, hc, hc_regs, qtd,
						  DWC_OTG_HC_XFER_FRAME_OVERRUN);

			halt_channel(hcd, hc, qtd, halt_status);
		}
		break;
	}

	disable_hc_int(hc_regs, frmovrun);

	return 1;
}