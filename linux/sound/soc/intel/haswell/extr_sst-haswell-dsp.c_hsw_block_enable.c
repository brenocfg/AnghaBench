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
typedef  int u32 ;
struct sst_mem_block {int /*<<< orphan*/  offset; int /*<<< orphan*/  index; int /*<<< orphan*/  type; struct sst_dsp* dsp; int /*<<< orphan*/  users; } ;
struct TYPE_2__ {scalar_t__ pci_cfg; } ;
struct sst_dsp {TYPE_1__ addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SST_VDRTCL2_DCLCGE ; 
 scalar_t__ SST_VDRTCTL0 ; 
 scalar_t__ SST_VDRTCTL2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hsw_block_get_bit (struct sst_mem_block*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sst_mem_block_dummy_read (struct sst_mem_block*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hsw_block_enable(struct sst_mem_block *block)
{
	struct sst_dsp *sst = block->dsp;
	u32 bit, val;

	if (block->users++ > 0)
		return 0;

	dev_dbg(block->dsp->dev, " enabled block %d:%d at offset 0x%x\n",
		block->type, block->index, block->offset);

	/* Disable core clock gating (VDRTCTL2.DCLCGE = 0) */
	val = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	val &= ~SST_VDRTCL2_DCLCGE;
	writel(val, sst->addr.pci_cfg + SST_VDRTCTL2);

	val = readl(sst->addr.pci_cfg + SST_VDRTCTL0);
	bit = hsw_block_get_bit(block);
	writel(val & ~bit, sst->addr.pci_cfg + SST_VDRTCTL0);

	/* wait 18 DSP clock ticks */
	udelay(10);

	/* Enable core clock gating (VDRTCTL2.DCLCGE = 1), delay 50 us */
	val = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	val |= SST_VDRTCL2_DCLCGE;
	writel(val, sst->addr.pci_cfg + SST_VDRTCTL2);

	udelay(50);

	/*add a dummy read before the SRAM block is written, otherwise the writing may miss bytes sometimes.*/
	sst_mem_block_dummy_read(block);
	return 0;
}