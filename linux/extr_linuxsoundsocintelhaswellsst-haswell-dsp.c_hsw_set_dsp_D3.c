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
struct TYPE_2__ {scalar_t__ pci_cfg; } ;
struct sst_dsp {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_CLKCTL ; 
 int /*<<< orphan*/  SST_CLKCTL_MASK ; 
 scalar_t__ SST_PMCS ; 
 int SST_PMCS_PS_MASK ; 
 int SST_VDRTCL0_D3PGD ; 
 int SST_VDRTCL0_D3SRAMPGD ; 
 int SST_VDRTCL0_DSRAMPGE_MASK ; 
 int SST_VDRTCL0_ISRAMPGE_MASK ; 
 int SST_VDRTCL2_APLLSE_MASK ; 
 int SST_VDRTCL2_DCLCGE ; 
 int SST_VDRTCL2_DTCGE ; 
 scalar_t__ SST_VDRTCTL0 ; 
 scalar_t__ SST_VDRTCTL2 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hsw_set_dsp_D3(struct sst_dsp *sst)
{
	u32 val;
	u32 reg;

	/* Disable core clock gating (VDRTCTL2.DCLCGE = 0) */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	reg &= ~(SST_VDRTCL2_DCLCGE | SST_VDRTCL2_DTCGE);
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL2);

	/* enable power gating and switch off DRAM & IRAM blocks */
	val = readl(sst->addr.pci_cfg + SST_VDRTCTL0);
	val |= SST_VDRTCL0_DSRAMPGE_MASK |
		SST_VDRTCL0_ISRAMPGE_MASK;
	val &= ~(SST_VDRTCL0_D3PGD | SST_VDRTCL0_D3SRAMPGD);
	writel(val, sst->addr.pci_cfg + SST_VDRTCTL0);

	/* switch off audio PLL */
	val = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	val |= SST_VDRTCL2_APLLSE_MASK;
	writel(val, sst->addr.pci_cfg + SST_VDRTCTL2);

	/* disable MCLK(clkctl.smos = 0) */
	sst_dsp_shim_update_bits_unlocked(sst, SST_CLKCTL,
		SST_CLKCTL_MASK, 0);

	/* Set D3 state, delay 50 us */
	val = readl(sst->addr.pci_cfg + SST_PMCS);
	val |= SST_PMCS_PS_MASK;
	writel(val, sst->addr.pci_cfg + SST_PMCS);
	udelay(50);

	/* Enable core clock gating (VDRTCTL2.DCLCGE = 1), delay 50 us */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	reg |= SST_VDRTCL2_DCLCGE | SST_VDRTCL2_DTCGE;
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL2);

	udelay(50);

}