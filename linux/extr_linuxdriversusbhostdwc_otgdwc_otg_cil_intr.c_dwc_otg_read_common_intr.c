#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_21__ {int d32; } ;
typedef  TYPE_6__ gintsts_data_t ;
struct TYPE_16__ {int wkupintr; int sessreqintr; int conidstschng; int otgintr; int modemismatch; int disconnect; int usbsuspend; int restoredone; int portintr; } ;
struct TYPE_22__ {int d32; TYPE_1__ b; } ;
typedef  TYPE_7__ gintmsk_data_t ;
struct TYPE_20__ {scalar_t__ glblintrmsk; } ;
struct TYPE_23__ {TYPE_5__ b; void* d32; } ;
typedef  TYPE_8__ gahbcfg_data_t ;
struct TYPE_24__ {TYPE_3__* fiq_state; } ;
typedef  TYPE_9__ dwc_otg_hcd_t ;
struct TYPE_15__ {TYPE_4__* core_global_regs; } ;
typedef  TYPE_10__ dwc_otg_core_if_t ;
struct TYPE_19__ {int /*<<< orphan*/  gahbcfg; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; } ;
struct TYPE_17__ {int d32; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; TYPE_2__ gintmsk_saved; } ;

/* Variables and functions */
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_10__*) ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 

__attribute__((used)) static inline uint32_t dwc_otg_read_common_intr(dwc_otg_core_if_t * core_if, gintmsk_data_t *reenable_gintmsk, dwc_otg_hcd_t *hcd)
{
	gahbcfg_data_t gahbcfg = {.d32 = 0 };
	gintsts_data_t gintsts;
	gintmsk_data_t gintmsk;
	gintmsk_data_t gintmsk_common = {.d32 = 0 };
	gintmsk_common.b.wkupintr = 1;
	gintmsk_common.b.sessreqintr = 1;
	gintmsk_common.b.conidstschng = 1;
	gintmsk_common.b.otgintr = 1;
	gintmsk_common.b.modemismatch = 1;
	gintmsk_common.b.disconnect = 1;
	gintmsk_common.b.usbsuspend = 1;
#ifdef CONFIG_USB_DWC_OTG_LPM
	gintmsk_common.b.lpmtranrcvd = 1;
#endif
	gintmsk_common.b.restoredone = 1;
	if(dwc_otg_is_device_mode(core_if))
	{
		/** @todo: The port interrupt occurs while in device
		 * mode. Added code to CIL to clear the interrupt for now!
		 */
		gintmsk_common.b.portintr = 1;
	}
	if(fiq_enable) {
		local_fiq_disable();
		fiq_fsm_spin_lock(&hcd->fiq_state->lock);
		gintsts.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintsts);
		gintmsk.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);
		/* Pull in the interrupts that the FIQ has masked */
		gintmsk.d32 |= ~(hcd->fiq_state->gintmsk_saved.d32);
		gintmsk.d32 |= gintmsk_common.d32;
		/* for the upstairs function to reenable - have to read it here in case FIQ triggers again */
		reenable_gintmsk->d32 = gintmsk.d32;
		fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
		local_fiq_enable();
	} else {
		gintsts.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintsts);
		gintmsk.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);
	}

	gahbcfg.d32 = DWC_READ_REG32(&core_if->core_global_regs->gahbcfg);

#ifdef DEBUG
	/* if any common interrupts set */
	if (gintsts.d32 & gintmsk_common.d32) {
		DWC_DEBUGPL(DBG_ANY, "common_intr: gintsts=%08x  gintmsk=%08x\n",
			    gintsts.d32, gintmsk.d32);
	}
#endif
	if (!fiq_enable){
		if (gahbcfg.b.glblintrmsk)
			return ((gintsts.d32 & gintmsk.d32) & gintmsk_common.d32);
		else
			return 0;
	} else {
		/* Our IRQ kicker is no longer the USB hardware, it's the MPHI interface.
		 * Can't trust the global interrupt mask bit in this case.
		 */
		return ((gintsts.d32 & gintmsk.d32) & gintmsk_common.d32);
	}

}