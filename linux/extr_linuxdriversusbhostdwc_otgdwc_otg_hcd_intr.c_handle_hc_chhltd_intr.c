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
typedef  int /*<<< orphan*/  dwc_otg_qtd_t ;
struct TYPE_11__ {TYPE_1__* core_if; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_12__ {int /*<<< orphan*/  halt_status; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_3__ dwc_hc_t ;
struct TYPE_10__ {scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_hc_chhltd_intr_dma (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_channel (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_chhltd_intr(dwc_otg_hcd_t * hcd,
				     dwc_hc_t * hc,
				     dwc_otg_hc_regs_t * hc_regs,
				     dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "Channel Halted--\n", hc->hc_num);

	if (hcd->core_if->dma_enable) {
		handle_hc_chhltd_intr_dma(hcd, hc, hc_regs, qtd);
	} else {
#ifdef DEBUG
		if (!halt_status_ok(hcd, hc, hc_regs, qtd)) {
			return 1;
		}
#endif
		release_channel(hcd, hc, qtd, hc->halt_status);
	}

	return 1;
}