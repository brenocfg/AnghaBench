#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_27__ {int d32; } ;
typedef  TYPE_11__ hfnum_data_t ;
struct TYPE_28__ {int d32; } ;
typedef  TYPE_12__ haintmsk_data_t ;
struct TYPE_38__ {int hcintr; int sofintr; scalar_t__ ptxfempty; scalar_t__ portintr; scalar_t__ i2cintr; scalar_t__ nptxfempty; scalar_t__ rxstsqlvl; } ;
struct TYPE_29__ {int d32; TYPE_5__ b; } ;
typedef  TYPE_13__ gintsts_data_t ;
struct TYPE_36__ {int portintr; } ;
struct TYPE_30__ {int d32; TYPE_3__ b; } ;
typedef  TYPE_14__ gintmsk_data_t ;
struct TYPE_31__ {int /*<<< orphan*/  lock; TYPE_17__* fiq_state; TYPE_16__* core_if; } ;
typedef  TYPE_15__ dwc_otg_hcd_t ;
struct TYPE_32__ {int hibernation_suspend; TYPE_10__* host_if; TYPE_4__* core_global_regs; } ;
typedef  TYPE_16__ dwc_otg_core_if_t ;
struct TYPE_42__ {int /*<<< orphan*/  haintmsk; int /*<<< orphan*/  hfnum; } ;
struct TYPE_41__ {int /*<<< orphan*/ * ctrl; int /*<<< orphan*/ * intstat; } ;
struct TYPE_34__ {int chint; } ;
struct TYPE_40__ {int /*<<< orphan*/  d32; TYPE_1__ b2; } ;
struct TYPE_35__ {int sofintr; } ;
struct TYPE_39__ {int d32; TYPE_2__ b; } ;
struct TYPE_37__ {int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; } ;
struct TYPE_33__ {int mphi_int_count; int /*<<< orphan*/  lock; scalar_t__ dwc_regs_base; TYPE_8__ mphi_regs; TYPE_7__ haintmsk_saved; TYPE_6__ gintmsk_saved; } ;
struct TYPE_26__ {TYPE_9__* host_global_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FIQDBG_INT ; 
 int /*<<< orphan*/  FIQ_WRITE (scalar_t__,int) ; 
 scalar_t__ GINTMSK ; 
 int HZ ; 
 int dwc_otg_hcd_handle_hc_intr (TYPE_15__*) ; 
 int dwc_otg_hcd_handle_np_tx_fifo_empty_intr (TYPE_15__*) ; 
 int dwc_otg_hcd_handle_perio_tx_fifo_empty_intr (TYPE_15__*) ; 
 int dwc_otg_hcd_handle_port_intr (TYPE_15__*) ; 
 int dwc_otg_hcd_handle_rx_status_q_level_intr (TYPE_15__*) ; 
 int dwc_otg_hcd_handle_sof_intr (TYPE_15__*) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_16__*) ; 
 scalar_t__ fiq_enable ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_print (int /*<<< orphan*/ ,TYPE_17__*,char*) ; 
 int /*<<< orphan*/  int_done ; 
 int jiffies ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 

int32_t dwc_otg_hcd_handle_intr(dwc_otg_hcd_t * dwc_otg_hcd)
{
	int retval = 0;
	static int last_time;
	dwc_otg_core_if_t *core_if = dwc_otg_hcd->core_if;
	gintsts_data_t gintsts;
	gintmsk_data_t gintmsk;
	hfnum_data_t hfnum;
	haintmsk_data_t haintmsk;

#ifdef DEBUG
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;

#endif

	gintsts.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintsts);
	gintmsk.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);

	/* Exit from ISR if core is hibernated */
	if (core_if->hibernation_suspend == 1) {
		goto exit_handler_routine;
	}
	DWC_SPINLOCK(dwc_otg_hcd->lock);
	/* Check if HOST Mode */
	if (dwc_otg_is_host_mode(core_if)) {
		if (fiq_enable) {
			local_fiq_disable();
			fiq_fsm_spin_lock(&dwc_otg_hcd->fiq_state->lock);
			/* Pull in from the FIQ's disabled mask */
			gintmsk.d32 = gintmsk.d32 | ~(dwc_otg_hcd->fiq_state->gintmsk_saved.d32);
			dwc_otg_hcd->fiq_state->gintmsk_saved.d32 = ~0;
		}

		if (fiq_fsm_enable && ( 0x0000FFFF & ~(dwc_otg_hcd->fiq_state->haintmsk_saved.b2.chint))) {
			gintsts.b.hcintr = 1;
		}

		/* Danger will robinson: fake a SOF if necessary */
		if (fiq_fsm_enable && (dwc_otg_hcd->fiq_state->gintmsk_saved.b.sofintr == 1)) {
			gintsts.b.sofintr = 1;
		}
		gintsts.d32 &= gintmsk.d32;

		if (fiq_enable) {
			fiq_fsm_spin_unlock(&dwc_otg_hcd->fiq_state->lock);
			local_fiq_enable();
		}

		if (!gintsts.d32) {
			goto exit_handler_routine;
		}

#ifdef DEBUG
		// We should be OK doing this because the common interrupts should already have been serviced
		/* Don't print debug message in the interrupt handler on SOF */
#ifndef DEBUG_SOF
		if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
			DWC_DEBUGPL(DBG_HCDI, "\n");
#endif

#ifdef DEBUG
#ifndef DEBUG_SOF
		if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
			DWC_DEBUGPL(DBG_HCDI,
				    "DWC OTG HCD Interrupt Detected gintsts&gintmsk=0x%08x core_if=%p\n",
				    gintsts.d32, core_if);
#endif
		hfnum.d32 = DWC_READ_REG32(&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum);
		if (gintsts.b.sofintr) {
			retval |= dwc_otg_hcd_handle_sof_intr(dwc_otg_hcd);
		}

		if (gintsts.b.rxstsqlvl) {
			retval |=
			    dwc_otg_hcd_handle_rx_status_q_level_intr
			    (dwc_otg_hcd);
		}
		if (gintsts.b.nptxfempty) {
			retval |=
			    dwc_otg_hcd_handle_np_tx_fifo_empty_intr
			    (dwc_otg_hcd);
		}
		if (gintsts.b.i2cintr) {
			/** @todo Implement i2cintr handler. */
		}
		if (gintsts.b.portintr) {

			gintmsk_data_t gintmsk = { .b.portintr = 1};
			retval |= dwc_otg_hcd_handle_port_intr(dwc_otg_hcd);
			if (fiq_enable) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&dwc_otg_hcd->fiq_state->lock);
				DWC_MODIFY_REG32(&dwc_otg_hcd->core_if->core_global_regs->gintmsk, 0, gintmsk.d32);
				fiq_fsm_spin_unlock(&dwc_otg_hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				DWC_MODIFY_REG32(&dwc_otg_hcd->core_if->core_global_regs->gintmsk, 0, gintmsk.d32);
			}
		}
		if (gintsts.b.hcintr) {
			retval |= dwc_otg_hcd_handle_hc_intr(dwc_otg_hcd);
		}
		if (gintsts.b.ptxfempty) {
			retval |=
			    dwc_otg_hcd_handle_perio_tx_fifo_empty_intr
			    (dwc_otg_hcd);
		}
#ifdef DEBUG
#ifndef DEBUG_SOF
		if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
		{
			DWC_DEBUGPL(DBG_HCDI,
				    "DWC OTG HCD Finished Servicing Interrupts\n");
			DWC_DEBUGPL(DBG_HCDV, "DWC OTG HCD gintsts=0x%08x\n",
				    DWC_READ_REG32(&global_regs->gintsts));
			DWC_DEBUGPL(DBG_HCDV, "DWC OTG HCD gintmsk=0x%08x\n",
				    DWC_READ_REG32(&global_regs->gintmsk));
		}
#endif

#ifdef DEBUG
#ifndef DEBUG_SOF
		if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
			DWC_DEBUGPL(DBG_HCDI, "\n");
#endif

	}

exit_handler_routine:
	if (fiq_enable)	{
		gintmsk_data_t gintmsk_new;
		haintmsk_data_t haintmsk_new;
		local_fiq_disable();
		fiq_fsm_spin_lock(&dwc_otg_hcd->fiq_state->lock);
		gintmsk_new.d32 = *(volatile uint32_t *)&dwc_otg_hcd->fiq_state->gintmsk_saved.d32;
		if(fiq_fsm_enable)
			haintmsk_new.d32 = *(volatile uint32_t *)&dwc_otg_hcd->fiq_state->haintmsk_saved.d32;
		else
			haintmsk_new.d32 = 0x0000FFFF;

		/* The FIQ could have sneaked another interrupt in. If so, don't clear MPHI */
		if ((gintmsk_new.d32 == ~0) && (haintmsk_new.d32 == 0x0000FFFF)) {
				DWC_WRITE_REG32(dwc_otg_hcd->fiq_state->mphi_regs.intstat, (1<<16));
				if (dwc_otg_hcd->fiq_state->mphi_int_count >= 50) {
					fiq_print(FIQDBG_INT, dwc_otg_hcd->fiq_state, "MPHI CLR");
					DWC_WRITE_REG32(dwc_otg_hcd->fiq_state->mphi_regs.ctrl, ((1<<31) + (1<<16)));
					while (!(DWC_READ_REG32(dwc_otg_hcd->fiq_state->mphi_regs.ctrl) & (1 << 17)))
						;
					DWC_WRITE_REG32(dwc_otg_hcd->fiq_state->mphi_regs.ctrl, (1<<31));
					dwc_otg_hcd->fiq_state->mphi_int_count = 0;
				}
				int_done++;
		}
		haintmsk.d32 = DWC_READ_REG32(&core_if->host_if->host_global_regs->haintmsk);
		/* Re-enable interrupts that the FIQ masked (first time round) */
		FIQ_WRITE(dwc_otg_hcd->fiq_state->dwc_regs_base + GINTMSK, gintmsk.d32);
		fiq_fsm_spin_unlock(&dwc_otg_hcd->fiq_state->lock);
		local_fiq_enable();

		if ((jiffies / HZ) > last_time) {
			//dwc_otg_qh_t *qh;
			//dwc_list_link_t *cur;
			/* Once a second output the fiq and irq numbers, useful for debug */
			last_time = jiffies / HZ;
		//	 DWC_WARN("np_kick=%d AHC=%d sched_frame=%d cur_frame=%d int_done=%d fiq_done=%d",
		//	dwc_otg_hcd->fiq_state->kick_np_queues, dwc_otg_hcd->available_host_channels,
		//	dwc_otg_hcd->fiq_state->next_sched_frame, hfnum.b.frnum, int_done, dwc_otg_hcd->fiq_state->fiq_done);
			 //printk(KERN_WARNING "Periodic queues:\n");
		}
	}

	DWC_SPINUNLOCK(dwc_otg_hcd->lock);
	return retval;
}