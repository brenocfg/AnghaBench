#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bdc_sr {int /*<<< orphan*/ * offset; } ;
struct TYPE_2__ {struct bdc_sr* sr_bds; int /*<<< orphan*/  dqp_index; scalar_t__ dma_addr; } ;
struct bdc {int /*<<< orphan*/  dev; TYPE_1__ srr; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int NUM_SR_ENTRIES ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void bdc_dbg_srr(struct bdc *bdc, u32 srr_num)
{
	struct bdc_sr *sr;
	dma_addr_t addr;
	int i;

	sr = bdc->srr.sr_bds;
	addr = bdc->srr.dma_addr;
	dev_vdbg(bdc->dev, "bdc_dbg_srr sr:%p dqp_index:%d\n",
						sr, bdc->srr.dqp_index);
	for (i = 0; i < NUM_SR_ENTRIES; i++) {
		sr = &bdc->srr.sr_bds[i];
		dev_vdbg(bdc->dev, "%llx %08x %08x %08x %08x\n",
					(unsigned long long)addr,
					le32_to_cpu(sr->offset[0]),
					le32_to_cpu(sr->offset[1]),
					le32_to_cpu(sr->offset[2]),
					le32_to_cpu(sr->offset[3]));
		addr += sizeof(*sr);
	}
}