#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ pktcnt; } ;
struct TYPE_14__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_2__ hctsiz_data_t ;
struct TYPE_15__ {scalar_t__ error_count; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;
struct TYPE_16__ {int /*<<< orphan*/  hctsiz; } ;
typedef  TYPE_4__ dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_17__ {int /*<<< orphan*/  ep_is_in; } ;
typedef  TYPE_5__ dwc_hc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  halt_channel (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_channel (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void complete_periodic_xfer(dwc_otg_hcd_t * hcd,
				   dwc_hc_t * hc,
				   dwc_otg_hc_regs_t * hc_regs,
				   dwc_otg_qtd_t * qtd,
				   dwc_otg_halt_status_e halt_status)
{
	hctsiz_data_t hctsiz;
	qtd->error_count = 0;

	hctsiz.d32 = DWC_READ_REG32(&hc_regs->hctsiz);
	if (!hc->ep_is_in || hctsiz.b.pktcnt == 0) {
		/* Core halts channel in these cases. */
		release_channel(hcd, hc, qtd, halt_status);
	} else {
		/* Flush any outstanding requests from the Tx queue. */
		halt_channel(hcd, hc, qtd, halt_status);
	}
}