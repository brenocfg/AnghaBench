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
struct msdc_host {int id; scalar_t__ base; } ;

/* Variables and functions */
 int DEFAULT_DTOC ; 
 int /*<<< orphan*/  FUC ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_1 ; 
 scalar_t__ MSDC_CFG ; 
 int MSDC_CFG_MODE ; 
 scalar_t__ MSDC_DAT_RDDLY0 ; 
 scalar_t__ MSDC_DAT_RDDLY1 ; 
 scalar_t__ MSDC_ECO_VER ; 
 scalar_t__ MSDC_INT ; 
 scalar_t__ MSDC_INTEN ; 
 scalar_t__ MSDC_IOCON ; 
 scalar_t__ MSDC_PAD_CTL0 ; 
 int MSDC_PAD_CTL0_CLKDRVN ; 
 int MSDC_PAD_CTL0_CLKDRVP ; 
 int /*<<< orphan*/  MSDC_PAD_CTL0_CLKSMT ; 
 scalar_t__ MSDC_PAD_CTL1 ; 
 int MSDC_PAD_CTL1_CMDDRVN ; 
 int MSDC_PAD_CTL1_CMDDRVP ; 
 int /*<<< orphan*/  MSDC_PAD_CTL1_CMDSMT ; 
 scalar_t__ MSDC_PAD_CTL2 ; 
 int MSDC_PAD_CTL2_DATDRVN ; 
 int MSDC_PAD_CTL2_DATDRVP ; 
 int /*<<< orphan*/  MSDC_PAD_CTL2_DATSMT ; 
 scalar_t__ MSDC_PAD_TUNE ; 
 scalar_t__ MSDC_PATCH_BIT0 ; 
 scalar_t__ MSDC_PATCH_BIT1 ; 
 int MSDC_PATCH_BIT1_CMD_RSP ; 
 int MSDC_PATCH_BIT1_WRDAT_CRCS ; 
 int /*<<< orphan*/  MSDC_PATCH_BIT_CKGEN_CK ; 
 scalar_t__ MSDC_PS ; 
 int MSDC_PS_CDEN ; 
 int MSDC_SDMMC ; 
 int /*<<< orphan*/  N_MSG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SDC_CFG ; 
 int SDC_CFG_DTOC ; 
 int /*<<< orphan*/  SDC_CFG_SDIO ; 
 int SDC_CFG_SDIOIDE ; 
 int /*<<< orphan*/  msdc_clr_fifo (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_set_buswidth (struct msdc_host*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void msdc_init_hw(struct msdc_host *host)
{

	/* Power on */
#if 0 /* --- by chhung */
	msdc_vcore_on(host);
	msdc_pin_reset(host, MSDC_PIN_PULL_UP);
	msdc_select_clksrc(host, hw->clk_src);
	enable_clock(PERI_MSDC0_PDN + host->id, "SD");
	msdc_vdd_on(host);
#endif /* end of --- */
	/* Configure to MMC/SD mode */
	sdr_set_field(host->base + MSDC_CFG, MSDC_CFG_MODE, MSDC_SDMMC);

	/* Reset */
	msdc_reset_hw(host);
	msdc_clr_fifo(host);

	/* Disable card detection */
	sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);

	/* Disable and clear all interrupts */
	sdr_clr_bits(host->base + MSDC_INTEN, readl(host->base + MSDC_INTEN));
	writel(readl(host->base + MSDC_INT), host->base + MSDC_INT);

#if 1
	/* reset tuning parameter */
	writel(0x00090000, host->base + MSDC_PAD_CTL0);
	writel(0x000A0000, host->base + MSDC_PAD_CTL1);
	writel(0x000A0000, host->base + MSDC_PAD_CTL2);
	// writel(  0x00000000, host->base + MSDC_PAD_TUNE);

	// for MT7620 E2 and afterward
	writel(0x84101010, host->base + MSDC_PAD_TUNE);

	// writel(0x00000000, host->base + MSDC_DAT_RDDLY0);

	// for MT7620 E2 and afterward
	writel(0x10101010, host->base + MSDC_DAT_RDDLY0);

	writel(0x00000000, host->base + MSDC_DAT_RDDLY1);
	writel(0x00000000, host->base + MSDC_IOCON);
#if 0 // use MT7620 default value: 0x403c004f
	/* bit0 modified: Rx Data Clock Source: 1 -> 2.0*/
	writel(0x003C000F, host->base + MSDC_PATCH_BIT0);
#endif

	if (readl(host->base + MSDC_ECO_VER) >= 4) {
		if (host->id == 1) {
			sdr_set_field(host->base + MSDC_PATCH_BIT1,
				      MSDC_PATCH_BIT1_WRDAT_CRCS, 1);
			sdr_set_field(host->base + MSDC_PATCH_BIT1,
				      MSDC_PATCH_BIT1_CMD_RSP,    1);

			/* internal clock: latch read data */
			sdr_set_bits(host->base + MSDC_PATCH_BIT0,
				     MSDC_PATCH_BIT_CKGEN_CK);
		}
	}
#endif

	/* for safety, should clear SDC_CFG.SDIO_INT_DET_EN & set SDC_CFG.SDIO in
	   pre-loader,uboot,kernel drivers. and SDC_CFG.SDIO_INT_DET_EN will be only
	   set when kernel driver wants to use SDIO bus interrupt */
	/* Configure to enable SDIO mode. it's must otherwise sdio cmd5 failed */
	sdr_set_bits(host->base + SDC_CFG, SDC_CFG_SDIO);

	/* disable detect SDIO device interupt function */
	sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);

	/* eneable SMT for glitch filter */
	sdr_set_bits(host->base + MSDC_PAD_CTL0, MSDC_PAD_CTL0_CLKSMT);
	sdr_set_bits(host->base + MSDC_PAD_CTL1, MSDC_PAD_CTL1_CMDSMT);
	sdr_set_bits(host->base + MSDC_PAD_CTL2, MSDC_PAD_CTL2_DATSMT);

#if 1
	/* set clk, cmd, dat pad driving */
	sdr_set_field(host->base + MSDC_PAD_CTL0, MSDC_PAD_CTL0_CLKDRVN, 4);
	sdr_set_field(host->base + MSDC_PAD_CTL0, MSDC_PAD_CTL0_CLKDRVP, 4);
	sdr_set_field(host->base + MSDC_PAD_CTL1, MSDC_PAD_CTL1_CMDDRVN, 4);
	sdr_set_field(host->base + MSDC_PAD_CTL1, MSDC_PAD_CTL1_CMDDRVP, 4);
	sdr_set_field(host->base + MSDC_PAD_CTL2, MSDC_PAD_CTL2_DATDRVN, 4);
	sdr_set_field(host->base + MSDC_PAD_CTL2, MSDC_PAD_CTL2_DATDRVP, 4);
#else
	sdr_set_field(host->base + MSDC_PAD_CTL0, MSDC_PAD_CTL0_CLKDRVN, 0);
	sdr_set_field(host->base + MSDC_PAD_CTL0, MSDC_PAD_CTL0_CLKDRVP, 0);
	sdr_set_field(host->base + MSDC_PAD_CTL1, MSDC_PAD_CTL1_CMDDRVN, 0);
	sdr_set_field(host->base + MSDC_PAD_CTL1, MSDC_PAD_CTL1_CMDDRVP, 0);
	sdr_set_field(host->base + MSDC_PAD_CTL2, MSDC_PAD_CTL2_DATDRVN, 0);
	sdr_set_field(host->base + MSDC_PAD_CTL2, MSDC_PAD_CTL2_DATDRVP, 0);
#endif

	/* set sampling edge */

	/* write crc timeout detection */
	sdr_set_field(host->base + MSDC_PATCH_BIT0, 1 << 30, 1);

	/* Configure to default data timeout */
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC, DEFAULT_DTOC);

	msdc_set_buswidth(host, MMC_BUS_WIDTH_1);

	N_MSG(FUC, "init hardware done!");
}