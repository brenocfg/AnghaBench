#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {long ARM_r8; long ARM_fp; long ARM_sp; int /*<<< orphan*/  ARM_r9; } ;
struct fiq_stack {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;
struct TYPE_13__ {TYPE_5__* fiq_state; scalar_t__ fiq_stack; TYPE_2__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_10__ {int /*<<< orphan*/  base; scalar_t__ mphi_base; } ;
struct TYPE_14__ {TYPE_3__ os_dep; TYPE_6__* hcd; } ;
typedef  TYPE_7__ dwc_otg_device_t ;
struct TYPE_11__ {scalar_t__ ctrl; scalar_t__ base; scalar_t__ intstat; scalar_t__ outddb; scalar_t__ outdda; } ;
struct TYPE_12__ {TYPE_4__ mphi_regs; int /*<<< orphan*/  dwc_regs_base; } ;
struct TYPE_9__ {TYPE_1__* core_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_WARN (char*,scalar_t__,...) ; 
 int INTERRUPT_VC_USB ; 
 int /*<<< orphan*/  _dwc_otg_fiq_stub ; 
 int /*<<< orphan*/  _dwc_otg_fiq_stub_end ; 
 scalar_t__ claim_fiq (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_fiq_fsm ; 
 scalar_t__ dwc_otg_fiq_nop ; 
 int /*<<< orphan*/  enable_fiq (int) ; 
 int /*<<< orphan*/  fh ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_fiq_handler (void*,int) ; 
 int /*<<< orphan*/  set_fiq_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hcd_init_fiq(void *cookie)
{
	dwc_otg_device_t *otg_dev = cookie;
	dwc_otg_hcd_t *dwc_otg_hcd = otg_dev->hcd;
#ifdef CONFIG_ARM64
	int retval = 0;
	int irq;
#else
	struct pt_regs regs;
	int irq;

	if (claim_fiq(&fh)) {
		DWC_ERROR("Can't claim FIQ");
		BUG();
	}
	DWC_WARN("FIQ on core %d", smp_processor_id());
	DWC_WARN("FIQ ASM at %px length %d", &_dwc_otg_fiq_stub, (int)(&_dwc_otg_fiq_stub_end - &_dwc_otg_fiq_stub));
	set_fiq_handler((void *) &_dwc_otg_fiq_stub, &_dwc_otg_fiq_stub_end - &_dwc_otg_fiq_stub);
	memset(&regs,0,sizeof(regs));

	regs.ARM_r8 = (long) dwc_otg_hcd->fiq_state;
	if (fiq_fsm_enable) {
		regs.ARM_r9 = dwc_otg_hcd->core_if->core_params->host_channels;
		//regs.ARM_r10 = dwc_otg_hcd->dma;
		regs.ARM_fp = (long) dwc_otg_fiq_fsm;
	} else {
		regs.ARM_fp = (long) dwc_otg_fiq_nop;
	}

	regs.ARM_sp = (long) dwc_otg_hcd->fiq_stack + (sizeof(struct fiq_stack) - 4);

//		__show_regs(&regs);
	set_fiq_regs(&regs);
#endif

	//Set the mphi periph to  the required registers
	dwc_otg_hcd->fiq_state->mphi_regs.base    = otg_dev->os_dep.mphi_base;
	dwc_otg_hcd->fiq_state->mphi_regs.ctrl    = otg_dev->os_dep.mphi_base + 0x4c;
	dwc_otg_hcd->fiq_state->mphi_regs.outdda  = otg_dev->os_dep.mphi_base + 0x28;
	dwc_otg_hcd->fiq_state->mphi_regs.outddb  = otg_dev->os_dep.mphi_base + 0x2c;
	dwc_otg_hcd->fiq_state->mphi_regs.intstat = otg_dev->os_dep.mphi_base + 0x50;
	dwc_otg_hcd->fiq_state->dwc_regs_base = otg_dev->os_dep.base;
	DWC_WARN("MPHI regs_base at %px", dwc_otg_hcd->fiq_state->mphi_regs.base);
	//Enable mphi peripheral
	writel((1<<31),dwc_otg_hcd->fiq_state->mphi_regs.ctrl);
#ifdef DEBUG
	if (readl(dwc_otg_hcd->fiq_state->mphi_regs.ctrl) & 0x80000000)
		DWC_WARN("MPHI periph has been enabled");
	else
		DWC_WARN("MPHI periph has NOT been enabled");
#endif
	// Enable FIQ interrupt from USB peripheral
#ifdef CONFIG_ARM64
	irq = platform_get_irq(otg_dev->os_dep.platformdev, 1);

	if (irq < 0) {
		DWC_ERROR("Can't get SIM-FIQ irq");
		return;
	}

	retval = request_irq(irq, fiq_irq_handler, 0, "dwc_otg_sim-fiq", dwc_otg_hcd);

	if (retval < 0) {
		DWC_ERROR("Unable to request SIM-FIQ irq\n");
		return;
	}

	simfiq_irq = irq;
#else
#ifdef CONFIG_GENERIC_IRQ_MULTI_HANDLER
	irq = platform_get_irq(otg_dev->os_dep.platformdev, 1);
#else
	irq = INTERRUPT_VC_USB;
#endif
	if (irq < 0) {
		DWC_ERROR("Can't get FIQ irq");
		return;
	}
	/*
	 * We could take an interrupt immediately after enabling the FIQ.
	 * Ensure coherency of hcd->fiq_state.
	 */
	smp_mb();
	enable_fiq(irq);
	local_fiq_enable();
#endif

}