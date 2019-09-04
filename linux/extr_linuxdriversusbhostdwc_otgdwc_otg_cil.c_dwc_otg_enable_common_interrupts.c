#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int modemismatch; int otgintr; int rxstsqlvl; int conidstschng; int wkupintr; int usbsuspend; int sessreqintr; scalar_t__ disconnect; } ;
struct TYPE_7__ {int d32; TYPE_1__ b; } ;
typedef  TYPE_2__ gintmsk_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  dma_enable; TYPE_4__* core_global_regs; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gotgint; } ;
typedef  TYPE_4__ dwc_otg_core_global_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dwc_otg_enable_common_interrupts(dwc_otg_core_if_t * core_if)
{
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;
	gintmsk_data_t intr_mask = {.d32 = 0 };

	/* Clear any pending OTG Interrupts */
	DWC_WRITE_REG32(&global_regs->gotgint, 0xFFFFFFFF);

	/* Clear any pending interrupts */
	DWC_WRITE_REG32(&global_regs->gintsts, 0xFFFFFFFF);

	/*
	 * Enable the interrupts in the GINTMSK.
	 */
	intr_mask.b.modemismatch = 1;
	intr_mask.b.otgintr = 1;

	if (!core_if->dma_enable) {
		intr_mask.b.rxstsqlvl = 1;
	}

	intr_mask.b.conidstschng = 1;
	intr_mask.b.wkupintr = 1;
	intr_mask.b.disconnect = 0;
	intr_mask.b.usbsuspend = 1;
	intr_mask.b.sessreqintr = 1;
#ifdef CONFIG_USB_DWC_OTG_LPM
	if (core_if->core_params->lpm_enable) {
		intr_mask.b.lpmtranrcvd = 1;
	}
#endif
	DWC_WRITE_REG32(&global_regs->gintmsk, intr_mask.d32);
}