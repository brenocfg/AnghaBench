#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {TYPE_4__* host_if; scalar_t__ dma_desc_enable; TYPE_2__* core_params; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_10__ {TYPE_3__** hc_regs; int /*<<< orphan*/ * hprt0; TYPE_1__* host_global_regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  hcdmab; int /*<<< orphan*/  hcdma; int /*<<< orphan*/  hctsiz; int /*<<< orphan*/  hcintmsk; int /*<<< orphan*/  hcint; int /*<<< orphan*/  hcsplt; int /*<<< orphan*/  hcchar; } ;
struct TYPE_8__ {int host_channels; } ;
struct TYPE_7__ {int /*<<< orphan*/  hflbaddr; int /*<<< orphan*/  haintmsk; int /*<<< orphan*/  haint; int /*<<< orphan*/  hptxsts; int /*<<< orphan*/  hfnum; int /*<<< orphan*/  hfir; int /*<<< orphan*/  hcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/  volatile*) ; 

void dwc_otg_dump_host_registers(dwc_otg_core_if_t * core_if)
{
	int i;
	volatile uint32_t *addr;

	DWC_PRINTF("Host Global Registers\n");
	addr = &core_if->host_if->host_global_regs->hcfg;
	DWC_PRINTF("HCFG		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->host_if->host_global_regs->hfir;
	DWC_PRINTF("HFIR		 @0x%08lX : 0x%08X\n",
		   (unsigned long)addr, DWC_READ_REG32(addr));
	addr = &core_if->host_if->host_global_regs->hfnum;
	DWC_PRINTF("HFNUM	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->host_if->host_global_regs->hptxsts;
	DWC_PRINTF("HPTXSTS	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->host_if->host_global_regs->haint;
	DWC_PRINTF("HAINT	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	addr = &core_if->host_if->host_global_regs->haintmsk;
	DWC_PRINTF("HAINTMSK	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));
	if (core_if->dma_desc_enable) {
		addr = &core_if->host_if->host_global_regs->hflbaddr;
		DWC_PRINTF("HFLBADDR	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
	}

	addr = core_if->host_if->hprt0;
	DWC_PRINTF("HPRT0	 @0x%08lX : 0x%08X\n", (unsigned long)addr,
		   DWC_READ_REG32(addr));

	for (i = 0; i < core_if->core_params->host_channels; i++) {
		DWC_PRINTF("Host Channel %d Specific Registers\n", i);
		addr = &core_if->host_if->hc_regs[i]->hcchar;
		DWC_PRINTF("HCCHAR	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->host_if->hc_regs[i]->hcsplt;
		DWC_PRINTF("HCSPLT	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->host_if->hc_regs[i]->hcint;
		DWC_PRINTF("HCINT	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->host_if->hc_regs[i]->hcintmsk;
		DWC_PRINTF("HCINTMSK	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->host_if->hc_regs[i]->hctsiz;
		DWC_PRINTF("HCTSIZ	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		addr = &core_if->host_if->hc_regs[i]->hcdma;
		DWC_PRINTF("HCDMA	 @0x%08lX : 0x%08X\n",
			   (unsigned long)addr, DWC_READ_REG32(addr));
		if (core_if->dma_desc_enable) {
			addr = &core_if->host_if->hc_regs[i]->hcdmab;
			DWC_PRINTF("HCDMAB	 @0x%08lX : 0x%08X\n",
				   (unsigned long)addr, DWC_READ_REG32(addr));
		}

	}
	return;
}