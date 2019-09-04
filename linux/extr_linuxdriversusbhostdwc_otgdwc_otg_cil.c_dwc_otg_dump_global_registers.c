#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int num_dev_perio_in_ep; int num_in_eps; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_10__ {scalar_t__ en_multiple_tx_fifo; int /*<<< orphan*/ * pcgcctl; TYPE_3__* core_global_regs; TYPE_2__ hwcfg4; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/ * dtxfsiz; int /*<<< orphan*/  hptxfsiz; int /*<<< orphan*/  adpctl; int /*<<< orphan*/  gdfifocfg; int /*<<< orphan*/  gpwrdn; int /*<<< orphan*/  glpmcfg; int /*<<< orphan*/  ghwcfg4; int /*<<< orphan*/  ghwcfg3; int /*<<< orphan*/  ghwcfg2; int /*<<< orphan*/  ghwcfg1; int /*<<< orphan*/  gsnpsid; int /*<<< orphan*/  guid; int /*<<< orphan*/  ggpio; int /*<<< orphan*/  gpvndctl; int /*<<< orphan*/  gi2cctl; int /*<<< orphan*/  gnptxsts; int /*<<< orphan*/  gnptxfsiz; int /*<<< orphan*/  grxfsiz; int /*<<< orphan*/  grxstsr; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; int /*<<< orphan*/  grstctl; int /*<<< orphan*/  gusbcfg; int /*<<< orphan*/  gahbcfg; int /*<<< orphan*/  gotgint; int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  dwc_otg_adp_read_reg (TYPE_4__*) ; 

void dwc_otg_dump_global_registers(dwc_otg_core_if_t * core_if)
{
	int i, ep_num;
	volatile uint32_t *addr;
	char *txfsiz;

	DWC_PRINTF("Core Global Registers\n");
	addr = &core_if->core_global_regs->gotgctl;
	DWC_PRINTF("GOTGCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gotgint;
	DWC_PRINTF("GOTGINT	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gahbcfg;
	DWC_PRINTF("GAHBCFG	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gusbcfg;
	DWC_PRINTF("GUSBCFG	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->grstctl;
	DWC_PRINTF("GRSTCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gintsts;
	DWC_PRINTF("GINTSTS	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gintmsk;
	DWC_PRINTF("GINTMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->grxstsr;
	DWC_PRINTF("GRXSTSR	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->grxfsiz;
	DWC_PRINTF("GRXFSIZ	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gnptxfsiz;
	DWC_PRINTF("GNPTXFSIZ @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gnptxsts;
	DWC_PRINTF("GNPTXSTS	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gi2cctl;
	DWC_PRINTF("GI2CCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gpvndctl;
	DWC_PRINTF("GPVNDCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->ggpio;
	DWC_PRINTF("GGPIO	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->guid;
	DWC_PRINTF("GUID		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gsnpsid;
	DWC_PRINTF("GSNPSID	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->ghwcfg1;
	DWC_PRINTF("GHWCFG1	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->ghwcfg2;
	DWC_PRINTF("GHWCFG2	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->ghwcfg3;
	DWC_PRINTF("GHWCFG3	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->ghwcfg4;
	DWC_PRINTF("GHWCFG4	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->glpmcfg;
	DWC_PRINTF("GLPMCFG	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gpwrdn;
	DWC_PRINTF("GPWRDN	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->gdfifocfg;
	DWC_PRINTF("GDFIFOCFG	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->core_global_regs->adpctl;
	DWC_PRINTF("ADPCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   dwc_otg_adp_read_reg(core_if));
	addr = &core_if->core_global_regs->hptxfsiz;
	DWC_PRINTF("HPTXFSIZ	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));

	if (core_if->en_multiple_tx_fifo == 0) {
		ep_num = core_if->hwcfg4.b.num_dev_perio_in_ep;
		txfsiz = "DPTXFSIZ";
	} else {
		ep_num = core_if->hwcfg4.b.num_in_eps;
		txfsiz = "DIENPTXF";
	}
	for (i = 0; i < ep_num; i++) {
		addr = &core_if->core_global_regs->dtxfsiz[i];
		DWC_PRINTF("%s[%d] @0x%08lX : 0x%08X\n", txfsiz, i + 1,
			   (unsigned long)addr, DWC_READ_REG32(addr));
	}
	addr = core_if->pcgcctl;
	DWC_PRINTF("PCGCCTL	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
}