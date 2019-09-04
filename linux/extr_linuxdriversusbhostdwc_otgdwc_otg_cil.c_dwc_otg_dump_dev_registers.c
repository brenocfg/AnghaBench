#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int dev_token_q_depth; scalar_t__ multi_proc_int; } ;
struct TYPE_12__ {TYPE_3__ b; } ;
struct TYPE_15__ {TYPE_6__* dev_if; scalar_t__ dma_enable; TYPE_4__ hwcfg2; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_14__ {int num_in_eps; int num_out_eps; TYPE_2__** out_ep_regs; TYPE_1__** in_ep_regs; TYPE_5__* dev_global_regs; } ;
struct TYPE_13__ {int /*<<< orphan*/ * doepeachintmsk; int /*<<< orphan*/ * diepeachintmsk; int /*<<< orphan*/  deachintmsk; int /*<<< orphan*/  deachint; int /*<<< orphan*/  dtknqr4_fifoemptymsk; int /*<<< orphan*/  dtknqr3_dthrctl; int /*<<< orphan*/  dvbuspulse; int /*<<< orphan*/  dvbusdis; int /*<<< orphan*/  dtknqr2; int /*<<< orphan*/  dtknqr1; int /*<<< orphan*/  daintmsk; int /*<<< orphan*/  daint; int /*<<< orphan*/  doepmsk; int /*<<< orphan*/  diepmsk; int /*<<< orphan*/  dsts; int /*<<< orphan*/  dctl; int /*<<< orphan*/  dcfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  doepdmab; int /*<<< orphan*/  doepdma; int /*<<< orphan*/  doeptsiz; int /*<<< orphan*/  doepint; int /*<<< orphan*/  doepctl; } ;
struct TYPE_9__ {int /*<<< orphan*/  diepdmab; int /*<<< orphan*/  dtxfsts; int /*<<< orphan*/  diepdma; int /*<<< orphan*/  dieptsiz; int /*<<< orphan*/  diepint; int /*<<< orphan*/  diepctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/  volatile*) ; 

void dwc_otg_dump_dev_registers(dwc_otg_core_if_t * core_if)
{
	int i;
	volatile uint32_t *addr;

	DWC_PRINTF("Device Global Registers\n");
	addr = &core_if->dev_if->dev_global_regs->dcfg;
	DWC_PRINTF("DCFG		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->dctl;
	DWC_PRINTF("DCTL		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->dsts;
	DWC_PRINTF("DSTS		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->diepmsk;
	DWC_PRINTF("DIEPMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->doepmsk;
	DWC_PRINTF("DOEPMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->daint;
	DWC_PRINTF("DAINT	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->daintmsk;
	DWC_PRINTF("DAINTMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->dev_if->dev_global_regs->dtknqr1;
	DWC_PRINTF("DTKNQR1	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	if (core_if->hwcfg2.b.dev_token_q_depth > 6) {
		addr = &core_if->dev_if->dev_global_regs->dtknqr2;
		DWC_PRINTF("DTKNQR2	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
	}

	addr = &core_if->dev_if->dev_global_regs->dvbusdis;
	DWC_PRINTF("DVBUSID	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));

	addr = &core_if->dev_if->dev_global_regs->dvbuspulse;
	DWC_PRINTF("DVBUSPULSE	@0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));

	addr = &core_if->dev_if->dev_global_regs->dtknqr3_dthrctl;
	DWC_PRINTF("DTKNQR3_DTHRCTL	 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));

	if (core_if->hwcfg2.b.dev_token_q_depth > 22) {
		addr = &core_if->dev_if->dev_global_regs->dtknqr4_fifoemptymsk;
		DWC_PRINTF("DTKNQR4	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
	}

	addr = &core_if->dev_if->dev_global_regs->dtknqr4_fifoemptymsk;
	DWC_PRINTF("FIFOEMPMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));

	if (core_if->hwcfg2.b.multi_proc_int) {

		addr = &core_if->dev_if->dev_global_regs->deachint;
		DWC_PRINTF("DEACHINT	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->dev_global_regs->deachintmsk;
		DWC_PRINTF("DEACHINTMSK	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));

		for (i = 0; i <= core_if->dev_if->num_in_eps; i++) {
			addr =
			    &core_if->dev_if->
			    dev_global_regs->diepeachintmsk[i];
			DWC_PRINTF("DIEPEACHINTMSK[%d]	 @0x%08lX : 0x%08X\n",
				   i, (unsigned long)addr,
				   DWC_READ_REG32(addr));
		}

		for (i = 0; i <= core_if->dev_if->num_out_eps; i++) {
			addr =
			    &core_if->dev_if->
			    dev_global_regs->doepeachintmsk[i];
			DWC_PRINTF("DOEPEACHINTMSK[%d]	 @0x%08lX : 0x%08X\n",
				   i, (unsigned long)addr,
				   DWC_READ_REG32(addr));
		}
	}

	for (i = 0; i <= core_if->dev_if->num_in_eps; i++) {
		DWC_PRINTF("Device IN EP %d Registers\n", i);
		addr = &core_if->dev_if->in_ep_regs[i]->diepctl;
		DWC_PRINTF("DIEPCTL	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->in_ep_regs[i]->diepint;
		DWC_PRINTF("DIEPINT	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->in_ep_regs[i]->dieptsiz;
		DWC_PRINTF("DIETSIZ	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->in_ep_regs[i]->diepdma;
		DWC_PRINTF("DIEPDMA	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->in_ep_regs[i]->dtxfsts;
		DWC_PRINTF("DTXFSTS	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->in_ep_regs[i]->diepdmab;
		DWC_PRINTF("DIEPDMAB	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, 0 /*DWC_READ_REG32(addr) */ );
	}

	for (i = 0; i <= core_if->dev_if->num_out_eps; i++) {
		DWC_PRINTF("Device OUT EP %d Registers\n", i);
		addr = &core_if->dev_if->out_ep_regs[i]->doepctl;
		DWC_PRINTF("DOEPCTL	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->out_ep_regs[i]->doepint;
		DWC_PRINTF("DOEPINT	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->out_ep_regs[i]->doeptsiz;
		DWC_PRINTF("DOETSIZ	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->dev_if->out_ep_regs[i]->doepdma;
		DWC_PRINTF("DOEPDMA	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		if (core_if->dma_enable) {	/* Don't access this register in SLAVE mode */
			addr = &core_if->dev_if->out_ep_regs[i]->doepdmab;
			DWC_PRINTF("DOEPDMAB	 @0x%08lX : 0x%08X\n",
				   (unsigned long)addr, DWC_READ_REG32(addr));
		}

	}
}