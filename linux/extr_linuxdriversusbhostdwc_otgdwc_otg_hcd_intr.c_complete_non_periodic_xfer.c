#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ nyet; } ;
struct TYPE_17__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ hcint_data_t ;
struct TYPE_18__ {scalar_t__ error_count; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;
struct TYPE_19__ {int /*<<< orphan*/  hcint; } ;
typedef  TYPE_5__ dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_20__ {scalar_t__ ep_is_in; TYPE_2__* qh; } ;
typedef  TYPE_6__ dwc_hc_t ;
struct TYPE_16__ {int ping_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_hc_int (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt_channel (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nyet ; 
 int /*<<< orphan*/  release_channel (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void complete_non_periodic_xfer(dwc_otg_hcd_t * hcd,
				       dwc_hc_t * hc,
				       dwc_otg_hc_regs_t * hc_regs,
				       dwc_otg_qtd_t * qtd,
				       dwc_otg_halt_status_e halt_status)
{
	hcint_data_t hcint;

	qtd->error_count = 0;

	hcint.d32 = DWC_READ_REG32(&hc_regs->hcint);
	if (hcint.b.nyet) {
		/*
		 * Got a NYET on the last transaction of the transfer. This
		 * means that the endpoint should be in the PING state at the
		 * beginning of the next transfer.
		 */
		hc->qh->ping_state = 1;
		clear_hc_int(hc_regs, nyet);
	}

	/*
	 * Always halt and release the host channel to make it available for
	 * more transfers. There may still be more phases for a control
	 * transfer or more data packets for a bulk transfer at this point,
	 * but the host channel is still halted. A channel will be reassigned
	 * to the transfer when the non-periodic schedule is processed after
	 * the channel is released. This allows transactions to be queued
	 * properly via dwc_otg_hcd_queue_transactions, which also enables the
	 * Tx FIFO Empty interrupt if necessary.
	 */
	if (hc->ep_is_in) {
		/*
		 * IN transfers in Slave mode require an explicit disable to
		 * halt the channel. (In DMA mode, this call simply releases
		 * the channel.)
		 */
		halt_channel(hcd, hc, qtd, halt_status);
	} else {
		/*
		 * The channel is automatically disabled by the core for OUT
		 * transfers in Slave mode.
		 */
		release_channel(hcd, hc, qtd, halt_status);
	}
}