#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct snd_sof_dev {scalar_t__* bar; } ;

/* Variables and functions */
 size_t BDW_DSP_BAR ; 
 size_t BDW_PCI_BAR ; 
 int ENODEV ; 
 scalar_t__ PCI_PMCS ; 
 int PCI_PMCS_PS_MASK ; 
 int PCI_VDRTCL0_D3PGD ; 
 int PCI_VDRTCL2_APLLSE_MASK ; 
 int PCI_VDRTCL2_DCLCGE ; 
 int PCI_VDRTCL2_DTCGE ; 
 scalar_t__ PCI_VDRTCTL0 ; 
 scalar_t__ PCI_VDRTCTL2 ; 
 scalar_t__ SHIM_CLKCTL ; 
 int SHIM_CLKCTL_DCPLCG ; 
 int SHIM_CLKCTL_MASK ; 
 int SHIM_CLKCTL_SCOE0 ; 
 scalar_t__ SHIM_CSR ; 
 scalar_t__ SHIM_CSR2 ; 
 int SHIM_CSR2_SDFD_SSP1 ; 
 int SHIM_CSR_DCS (int) ; 
 int SHIM_CSR_DCS_MASK ; 
 int SHIM_CSR_LPCS ; 
 int SHIM_CSR_S1IOCS ; 
 int SHIM_CSR_SBCS1 ; 
 int SHIM_CSR_STALL ; 
 int /*<<< orphan*/  SHIM_HMDC ; 
 int SHIM_HMDC_HDDA_E0_ALLCH ; 
 int SHIM_HMDC_HDDA_E1_ALLCH ; 
 int /*<<< orphan*/  SHIM_IMRD ; 
 int SHIM_IMRD_BUSY ; 
 int SHIM_IMRD_DMAC ; 
 int SHIM_IMRD_DONE ; 
 int SHIM_IMRD_SSP0 ; 
 int /*<<< orphan*/  SHIM_IMRX ; 
 int SHIM_IMRX_BUSY ; 
 int SHIM_IMRX_DONE ; 
 int SHIM_IPCD ; 
 int SHIM_IPCX ; 
 int /*<<< orphan*/  bdw_reset (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,size_t,scalar_t__,int,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_write (struct snd_sof_dev*,size_t,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bdw_set_dsp_D0(struct snd_sof_dev *sdev)
{
	int tries = 10;
	u32 reg;

	/* Disable core clock gating (VDRTCTL2.DCLCGE = 0) */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE, 0);

	/* Disable D3PG (VDRTCTL0.D3PGD = 1) */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL0,
					 PCI_VDRTCL0_D3PGD, PCI_VDRTCL0_D3PGD);

	/* Set D0 state */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_PMCS,
					 PCI_PMCS_PS_MASK, 0);

	/* check that ADSP shim is enabled */
	while (tries--) {
		reg = readl(sdev->bar[BDW_PCI_BAR] + PCI_PMCS)
			& PCI_PMCS_PS_MASK;
		if (reg == 0)
			goto finish;

		msleep(20);
	}

	return -ENODEV;

finish:
	/*
	 * select SSP1 19.2MHz base clock, SSP clock 0,
	 * turn off Low Power Clock
	 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_S1IOCS | SHIM_CSR_SBCS1 |
					 SHIM_CSR_LPCS, 0x0);

	/* stall DSP core, set clk to 192/96Mhz */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,
					 SHIM_CSR, SHIM_CSR_STALL |
					 SHIM_CSR_DCS_MASK,
					 SHIM_CSR_STALL |
					 SHIM_CSR_DCS(4));

	/* Set 24MHz MCLK, prevent local clock gating, enable SSP0 clock */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CLKCTL,
					 SHIM_CLKCTL_MASK |
					 SHIM_CLKCTL_DCPLCG |
					 SHIM_CLKCTL_SCOE0,
					 SHIM_CLKCTL_MASK |
					 SHIM_CLKCTL_DCPLCG |
					 SHIM_CLKCTL_SCOE0);

	/* Stall and reset core, set CSR */
	bdw_reset(sdev);

	/* Enable core clock gating (VDRTCTL2.DCLCGE = 1), delay 50 us */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE);

	usleep_range(50, 55);

	/* switch on audio PLL */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_APLLSE_MASK, 0);

	/*
	 * set default power gating control, enable power gating control for
	 * all blocks. that is, can't be accessed, please enable each block
	 * before accessing.
	 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL0,
					 0xfffffffC, 0x0);

	/* disable DMA finish function for SSP0 & SSP1 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,  SHIM_CSR2,
					 SHIM_CSR2_SDFD_SSP1,
					 SHIM_CSR2_SDFD_SSP1);

	/* set on-demond mode on engine 0,1 for all channels */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH);

	/* Enable Interrupt from both sides */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_IMRX,
				(SHIM_IMRX_BUSY | SHIM_IMRX_DONE), 0x0);
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_IMRD,
				(SHIM_IMRD_DONE | SHIM_IMRD_BUSY |
				SHIM_IMRD_SSP0 | SHIM_IMRD_DMAC), 0x0);

	/* clear IPC registers */
	snd_sof_dsp_write(sdev, BDW_DSP_BAR, SHIM_IPCX, 0x0);
	snd_sof_dsp_write(sdev, BDW_DSP_BAR, SHIM_IPCD, 0x0);
	snd_sof_dsp_write(sdev, BDW_DSP_BAR, 0x80, 0x6);
	snd_sof_dsp_write(sdev, BDW_DSP_BAR, 0xe0, 0x300a);

	return 0;
}