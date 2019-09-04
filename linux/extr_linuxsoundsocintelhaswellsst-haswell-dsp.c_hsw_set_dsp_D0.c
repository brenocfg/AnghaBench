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
 int ENODEV ; 
 int /*<<< orphan*/  SST_CLKCTL ; 
 int SST_CLKCTL_DCPLCG ; 
 int SST_CLKCTL_MASK ; 
 int SST_CLKCTL_SCOE0 ; 
 int /*<<< orphan*/  SST_CSR ; 
 int /*<<< orphan*/  SST_CSR2 ; 
 int SST_CSR2_SDFD_SSP1 ; 
 int SST_CSR_DCS (int) ; 
 int SST_CSR_DCS_MASK ; 
 int SST_CSR_LPCS ; 
 int SST_CSR_S1IOCS ; 
 int SST_CSR_SBCS1 ; 
 int SST_CSR_STALL ; 
 int /*<<< orphan*/  SST_HMDC ; 
 int SST_HMDC_HDDA_E0_ALLCH ; 
 int SST_HMDC_HDDA_E1_ALLCH ; 
 int /*<<< orphan*/  SST_IMRD ; 
 int SST_IMRD_BUSY ; 
 int SST_IMRD_DMAC ; 
 int SST_IMRD_DONE ; 
 int SST_IMRD_SSP0 ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int SST_IMRX_BUSY ; 
 int SST_IMRX_DONE ; 
 int SST_IPCD ; 
 int SST_IPCX ; 
 scalar_t__ SST_PMCS ; 
 int SST_PMCS_PS_MASK ; 
 int SST_VDRTCL0_D3PGD ; 
 int SST_VDRTCL0_DSRAMPGE_MASK ; 
 int SST_VDRTCL0_DSRAMPGE_SHIFT ; 
 int SST_VDRTCL0_ISRAMPGE_MASK ; 
 int SST_VDRTCL2_APLLSE_MASK ; 
 int SST_VDRTCL2_DCLCGE ; 
 int SST_VDRTCL2_DTCGE ; 
 scalar_t__ SST_VDRTCTL0 ; 
 scalar_t__ SST_VDRTCTL2 ; 
 int /*<<< orphan*/  hsw_reset (struct sst_dsp*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sst_dsp_shim_write (struct sst_dsp*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hsw_set_dsp_D0(struct sst_dsp *sst)
{
	int tries = 10;
	u32 reg, fw_dump_bit;

	/* Disable core clock gating (VDRTCTL2.DCLCGE = 0) */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	reg &= ~(SST_VDRTCL2_DCLCGE | SST_VDRTCL2_DTCGE);
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL2);

	/* Disable D3PG (VDRTCTL0.D3PGD = 1) */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL0);
	reg |= SST_VDRTCL0_D3PGD;
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL0);

	/* Set D0 state */
	reg = readl(sst->addr.pci_cfg + SST_PMCS);
	reg &= ~SST_PMCS_PS_MASK;
	writel(reg, sst->addr.pci_cfg + SST_PMCS);

	/* check that ADSP shim is enabled */
	while (tries--) {
		reg = readl(sst->addr.pci_cfg + SST_PMCS) & SST_PMCS_PS_MASK;
		if (reg == 0)
			goto finish;

		msleep(1);
	}

	return -ENODEV;

finish:
	/* select SSP1 19.2MHz base clock, SSP clock 0, turn off Low Power Clock */
	sst_dsp_shim_update_bits_unlocked(sst, SST_CSR,
		SST_CSR_S1IOCS | SST_CSR_SBCS1 | SST_CSR_LPCS, 0x0);

	/* stall DSP core, set clk to 192/96Mhz */
	sst_dsp_shim_update_bits_unlocked(sst,
		SST_CSR, SST_CSR_STALL | SST_CSR_DCS_MASK,
		SST_CSR_STALL | SST_CSR_DCS(4));

	/* Set 24MHz MCLK, prevent local clock gating, enable SSP0 clock */
	sst_dsp_shim_update_bits_unlocked(sst, SST_CLKCTL,
		SST_CLKCTL_MASK | SST_CLKCTL_DCPLCG | SST_CLKCTL_SCOE0,
		SST_CLKCTL_MASK | SST_CLKCTL_DCPLCG | SST_CLKCTL_SCOE0);

	/* Stall and reset core, set CSR */
	hsw_reset(sst);

	/* Enable core clock gating (VDRTCTL2.DCLCGE = 1), delay 50 us */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	reg |= SST_VDRTCL2_DCLCGE | SST_VDRTCL2_DTCGE;
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL2);

	udelay(50);

	/* switch on audio PLL */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL2);
	reg &= ~SST_VDRTCL2_APLLSE_MASK;
	writel(reg, sst->addr.pci_cfg + SST_VDRTCTL2);

	/* set default power gating control, enable power gating control for all blocks. that is,
	can't be accessed, please enable each block before accessing. */
	reg = readl(sst->addr.pci_cfg + SST_VDRTCTL0);
	reg |= SST_VDRTCL0_DSRAMPGE_MASK | SST_VDRTCL0_ISRAMPGE_MASK;
	/* for D0, always enable the block(DSRAM[0]) used for FW dump */
	fw_dump_bit = 1 << SST_VDRTCL0_DSRAMPGE_SHIFT;
	writel(reg & ~fw_dump_bit, sst->addr.pci_cfg + SST_VDRTCTL0);


	/* disable DMA finish function for SSP0 & SSP1 */
	sst_dsp_shim_update_bits_unlocked(sst, SST_CSR2, SST_CSR2_SDFD_SSP1,
		SST_CSR2_SDFD_SSP1);

	/* set on-demond mode on engine 0,1 for all channels */
	sst_dsp_shim_update_bits(sst, SST_HMDC,
			SST_HMDC_HDDA_E0_ALLCH | SST_HMDC_HDDA_E1_ALLCH,
			SST_HMDC_HDDA_E0_ALLCH | SST_HMDC_HDDA_E1_ALLCH);

	/* Enable Interrupt from both sides */
	sst_dsp_shim_update_bits(sst, SST_IMRX, (SST_IMRX_BUSY | SST_IMRX_DONE),
				 0x0);
	sst_dsp_shim_update_bits(sst, SST_IMRD, (SST_IMRD_DONE | SST_IMRD_BUSY |
				SST_IMRD_SSP0 | SST_IMRD_DMAC), 0x0);

	/* clear IPC registers */
	sst_dsp_shim_write(sst, SST_IPCX, 0x0);
	sst_dsp_shim_write(sst, SST_IPCD, 0x0);
	sst_dsp_shim_write(sst, 0x80, 0x6);
	sst_dsp_shim_write(sst, 0xe0, 0x300a);

	return 0;
}