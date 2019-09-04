#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int u16 ;
struct radio_regs {scalar_t__ init_a; scalar_t__ init_g; } ;
struct chan_info_nphy_radio205x {int RF_SYN_pll_vcocal1; int RF_SYN_pll_vcocal2; int RF_SYN_pll_refdiv; int RF_SYN_pll_mmd2; int RF_SYN_pll_mmd1; int RF_SYN_pll_loopfilter1; int RF_SYN_pll_loopfilter2; int RF_SYN_pll_loopfilter3; int RF_SYN_pll_loopfilter4; int RF_SYN_pll_loopfilter5; int RF_SYN_reserved_addr27; int RF_SYN_reserved_addr28; int RF_SYN_reserved_addr29; int RF_SYN_logen_VCOBUF1; int RF_SYN_logen_MIXER2; int RF_SYN_logen_BUF3; int RF_SYN_logen_BUF4; int RF_RX0_lnaa_tune; int RF_RX0_lnag_tune; int RF_TX0_intpaa_boost_tune; int RF_TX0_intpag_boost_tune; int RF_TX0_pada_boost_tune; int RF_TX0_padg_boost_tune; int RF_TX0_pgaa_boost_tune; int RF_TX0_pgag_boost_tune; int RF_TX0_mixa_boost_tune; int RF_TX0_mixg_boost_tune; int RF_RX1_lnaa_tune; int RF_RX1_lnag_tune; int RF_TX1_intpaa_boost_tune; int RF_TX1_intpag_boost_tune; int RF_TX1_pada_boost_tune; int RF_TX1_padg_boost_tune; int RF_TX1_pgaa_boost_tune; int RF_TX1_pgag_boost_tune; int RF_TX1_mixa_boost_tune; int RF_TX1_mixg_boost_tune; } ;
struct TYPE_3__ {int radiorev; scalar_t__ phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ bw; int phy_pabias; TYPE_2__* sh; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;
struct TYPE_4__ {int boardflags2; scalar_t__ chip; scalar_t__ chippkg; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM43224 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43225 ; 
 scalar_t__ BCMA_CHIP_ID_BCM4716 ; 
 scalar_t__ BCMA_CHIP_ID_BCM47162 ; 
 scalar_t__ BCMA_PKG_ID_BCM43224_FAB_SMIC ; 
 int BFL2_APLL_WAR ; 
 int BFL2_GPLL_WAR ; 
 int BFL2_GPLL_WAR2 ; 
 int CHAN5G_FREQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTPAA_BOOST_TUNE ; 
 int /*<<< orphan*/  INTPAA_CASCBIAS ; 
 int /*<<< orphan*/  INTPAA_IAUX_STAT ; 
 int /*<<< orphan*/  INTPAA_IMAIN_STAT ; 
 int /*<<< orphan*/  INTPAG_BOOST_TUNE ; 
 int /*<<< orphan*/  INTPAG_CASCBIAS ; 
 int /*<<< orphan*/  INTPAG_IAUX_STAT ; 
 int /*<<< orphan*/  INTPAG_IMAIN_STAT ; 
 int /*<<< orphan*/  MIXA_BOOST_TUNE ; 
 int /*<<< orphan*/  MIXG_BOOST_TUNE ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PADA_BOOST_TUNE ; 
 int /*<<< orphan*/  PADA_CASCBIAS ; 
 int /*<<< orphan*/  PADG_BOOST_TUNE ; 
 int /*<<< orphan*/  PADG_IDAC ; 
 int /*<<< orphan*/  PA_SPARE1 ; 
 int /*<<< orphan*/  PA_SPARE2 ; 
 int /*<<< orphan*/  PGAA_BOOST_TUNE ; 
 int /*<<< orphan*/  PGAG_BOOST_TUNE ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int /*<<< orphan*/  RADIO_2056 ; 
 int RADIO_2056_RX0 ; 
 int RADIO_2056_RX1 ; 
 int RADIO_2056_RX_LNAA_TUNE ; 
 int RADIO_2056_RX_LNAG_TUNE ; 
 int RADIO_2056_SYN ; 
 int RADIO_2056_SYN_LOGEN_BUF3 ; 
 int RADIO_2056_SYN_LOGEN_BUF4 ; 
 int RADIO_2056_SYN_LOGEN_MIXER2 ; 
 int RADIO_2056_SYN_LOGEN_VCOBUF1 ; 
 int RADIO_2056_SYN_PLL_CP2 ; 
 int RADIO_2056_SYN_PLL_LOOPFILTER1 ; 
 int RADIO_2056_SYN_PLL_LOOPFILTER2 ; 
 int RADIO_2056_SYN_PLL_LOOPFILTER3 ; 
 int RADIO_2056_SYN_PLL_LOOPFILTER4 ; 
 int RADIO_2056_SYN_PLL_LOOPFILTER5 ; 
 int RADIO_2056_SYN_PLL_MMD1 ; 
 int RADIO_2056_SYN_PLL_MMD2 ; 
 int RADIO_2056_SYN_PLL_REFDIV ; 
 int RADIO_2056_SYN_PLL_VCOCAL1 ; 
 int RADIO_2056_SYN_PLL_VCOCAL2 ; 
 int RADIO_2056_SYN_RESERVED_ADDR27 ; 
 int RADIO_2056_SYN_RESERVED_ADDR28 ; 
 int RADIO_2056_SYN_RESERVED_ADDR29 ; 
 int RADIO_2056_TX0 ; 
 int RADIO_2056_TX1 ; 
 int RADIO_2056_TX_INTPAA_BOOST_TUNE ; 
 int RADIO_2056_TX_INTPAG_BOOST_TUNE ; 
 int RADIO_2056_TX_MIXA_BOOST_TUNE ; 
 int RADIO_2056_TX_MIXG_BOOST_TUNE ; 
 int RADIO_2056_TX_PADA_BOOST_TUNE ; 
 int RADIO_2056_TX_PADG_BOOST_TUNE ; 
 int RADIO_2056_TX_PGAA_BOOST_TUNE ; 
 int RADIO_2056_TX_PGAG_BOOST_TUNE ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TXSPARE1 ; 
 scalar_t__ WL_CHANSPEC_BW_40 ; 
 int /*<<< orphan*/  WRITE_RADIO_REG2 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct radio_regs* regs_SYN_2056 ; 
 struct radio_regs* regs_SYN_2056_A1 ; 
 struct radio_regs* regs_SYN_2056_rev11 ; 
 struct radio_regs* regs_SYN_2056_rev5 ; 
 struct radio_regs* regs_SYN_2056_rev6 ; 
 struct radio_regs* regs_SYN_2056_rev7 ; 
 struct radio_regs* regs_SYN_2056_rev8 ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_phy_radio205x_vcocal_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_chanspec_radio2056_setup(struct brcms_phy *pi,
				 const struct chan_info_nphy_radio205x *ci)
{
	const struct radio_regs *regs_SYN_2056_ptr = NULL;

	write_radio_reg(pi,
			RADIO_2056_SYN_PLL_VCOCAL1 | RADIO_2056_SYN,
			ci->RF_SYN_pll_vcocal1);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_VCOCAL2 | RADIO_2056_SYN,
			ci->RF_SYN_pll_vcocal2);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_REFDIV | RADIO_2056_SYN,
			ci->RF_SYN_pll_refdiv);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_MMD2 | RADIO_2056_SYN,
			ci->RF_SYN_pll_mmd2);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_MMD1 | RADIO_2056_SYN,
			ci->RF_SYN_pll_mmd1);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER1 | RADIO_2056_SYN,
			ci->RF_SYN_pll_loopfilter1);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER2 | RADIO_2056_SYN,
			ci->RF_SYN_pll_loopfilter2);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER3 | RADIO_2056_SYN,
			ci->RF_SYN_pll_loopfilter3);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER4 | RADIO_2056_SYN,
			ci->RF_SYN_pll_loopfilter4);
	write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER5 | RADIO_2056_SYN,
			ci->RF_SYN_pll_loopfilter5);
	write_radio_reg(pi, RADIO_2056_SYN_RESERVED_ADDR27 | RADIO_2056_SYN,
			ci->RF_SYN_reserved_addr27);
	write_radio_reg(pi, RADIO_2056_SYN_RESERVED_ADDR28 | RADIO_2056_SYN,
			ci->RF_SYN_reserved_addr28);
	write_radio_reg(pi, RADIO_2056_SYN_RESERVED_ADDR29 | RADIO_2056_SYN,
			ci->RF_SYN_reserved_addr29);
	write_radio_reg(pi, RADIO_2056_SYN_LOGEN_VCOBUF1 | RADIO_2056_SYN,
			ci->RF_SYN_logen_VCOBUF1);
	write_radio_reg(pi, RADIO_2056_SYN_LOGEN_MIXER2 | RADIO_2056_SYN,
			ci->RF_SYN_logen_MIXER2);
	write_radio_reg(pi, RADIO_2056_SYN_LOGEN_BUF3 | RADIO_2056_SYN,
			ci->RF_SYN_logen_BUF3);
	write_radio_reg(pi, RADIO_2056_SYN_LOGEN_BUF4 | RADIO_2056_SYN,
			ci->RF_SYN_logen_BUF4);

	write_radio_reg(pi,
			RADIO_2056_RX_LNAA_TUNE | RADIO_2056_RX0,
			ci->RF_RX0_lnaa_tune);
	write_radio_reg(pi, RADIO_2056_RX_LNAG_TUNE | RADIO_2056_RX0,
			ci->RF_RX0_lnag_tune);
	write_radio_reg(pi, RADIO_2056_TX_INTPAA_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_intpaa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_INTPAG_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_intpag_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PADA_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_pada_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PADG_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_padg_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PGAA_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_pgaa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PGAG_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_pgag_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_MIXA_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_mixa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_MIXG_BOOST_TUNE | RADIO_2056_TX0,
			ci->RF_TX0_mixg_boost_tune);

	write_radio_reg(pi,
			RADIO_2056_RX_LNAA_TUNE | RADIO_2056_RX1,
			ci->RF_RX1_lnaa_tune);
	write_radio_reg(pi, RADIO_2056_RX_LNAG_TUNE | RADIO_2056_RX1,
			ci->RF_RX1_lnag_tune);
	write_radio_reg(pi, RADIO_2056_TX_INTPAA_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_intpaa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_INTPAG_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_intpag_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PADA_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_pada_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PADG_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_padg_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PGAA_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_pgaa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_PGAG_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_pgag_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_MIXA_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_mixa_boost_tune);
	write_radio_reg(pi, RADIO_2056_TX_MIXG_BOOST_TUNE | RADIO_2056_TX1,
			ci->RF_TX1_mixg_boost_tune);

	if (NREV_IS(pi->pubpi.phy_rev, 3))
		regs_SYN_2056_ptr = regs_SYN_2056;
	else if (NREV_IS(pi->pubpi.phy_rev, 4))
		regs_SYN_2056_ptr = regs_SYN_2056_A1;
	else {
		switch (pi->pubpi.radiorev) {
		case 5:
			regs_SYN_2056_ptr = regs_SYN_2056_rev5;
			break;
		case 6:
			regs_SYN_2056_ptr = regs_SYN_2056_rev6;
			break;
		case 7:
		case 9:
			regs_SYN_2056_ptr = regs_SYN_2056_rev7;
			break;
		case 8:
			regs_SYN_2056_ptr = regs_SYN_2056_rev8;
			break;
		case 11:
			regs_SYN_2056_ptr = regs_SYN_2056_rev11;
			break;
		}
	}
	if (CHSPEC_IS2G(pi->radio_chanspec))
		write_radio_reg(pi, RADIO_2056_SYN_PLL_CP2 |
				RADIO_2056_SYN,
				(u16) regs_SYN_2056_ptr[0x49 - 2].init_g);
	else
		write_radio_reg(pi, RADIO_2056_SYN_PLL_CP2 |
				RADIO_2056_SYN,
				(u16) regs_SYN_2056_ptr[0x49 - 2].init_a);

	if (pi->sh->boardflags2 & BFL2_GPLL_WAR) {
		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER1 |
					RADIO_2056_SYN, 0x1f);
			write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER2 |
					RADIO_2056_SYN, 0x1f);

			if ((pi->sh->chip == BCMA_CHIP_ID_BCM4716) ||
			    (pi->sh->chip == BCMA_CHIP_ID_BCM47162)) {
				write_radio_reg(pi,
						RADIO_2056_SYN_PLL_LOOPFILTER4 |
						RADIO_2056_SYN, 0x14);
				write_radio_reg(pi,
						RADIO_2056_SYN_PLL_CP2 |
						RADIO_2056_SYN, 0x00);
			} else {
				write_radio_reg(pi,
						RADIO_2056_SYN_PLL_LOOPFILTER4 |
						RADIO_2056_SYN, 0xb);
				write_radio_reg(pi,
						RADIO_2056_SYN_PLL_CP2 |
						RADIO_2056_SYN, 0x14);
			}
		}
	}

	if ((pi->sh->boardflags2 & BFL2_GPLL_WAR2) &&
	    (CHSPEC_IS2G(pi->radio_chanspec))) {
		write_radio_reg(pi,
				RADIO_2056_SYN_PLL_LOOPFILTER1 | RADIO_2056_SYN,
				0x1f);
		write_radio_reg(pi,
				RADIO_2056_SYN_PLL_LOOPFILTER2 | RADIO_2056_SYN,
				0x1f);
		write_radio_reg(pi,
				RADIO_2056_SYN_PLL_LOOPFILTER4 | RADIO_2056_SYN,
				0xb);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_CP2 | RADIO_2056_SYN,
				0x20);
	}

	if (pi->sh->boardflags2 & BFL2_APLL_WAR) {
		if (CHSPEC_IS5G(pi->radio_chanspec)) {
			write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER1 |
					RADIO_2056_SYN, 0x1f);
			write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER2 |
					RADIO_2056_SYN, 0x1f);
			write_radio_reg(pi, RADIO_2056_SYN_PLL_LOOPFILTER4 |
					RADIO_2056_SYN, 0x5);
			write_radio_reg(pi, RADIO_2056_SYN_PLL_CP2 |
					RADIO_2056_SYN, 0xc);
		}
	}

	if (PHY_IPA(pi) && CHSPEC_IS2G(pi->radio_chanspec)) {
		u16 pag_boost_tune;
		u16 padg_boost_tune;
		u16 pgag_boost_tune;
		u16 mixg_boost_tune;
		u16 bias, cascbias;
		uint core;

		for (core = 0; core < pi->pubpi.phy_corenum; core++) {

			if (NREV_GE(pi->pubpi.phy_rev, 5)) {

				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 PADG_IDAC, 0xcc);

				if ((pi->sh->chip == BCMA_CHIP_ID_BCM4716) ||
				    (pi->sh->chip == BCMA_CHIP_ID_BCM47162)) {
					bias = 0x40;
					cascbias = 0x45;
					pag_boost_tune = 0x5;
					pgag_boost_tune = 0x33;
					padg_boost_tune = 0x77;
					mixg_boost_tune = 0x55;
				} else {
					bias = 0x25;
					cascbias = 0x20;

					if ((pi->sh->chip == BCMA_CHIP_ID_BCM43224 ||
					     pi->sh->chip == BCMA_CHIP_ID_BCM43225) &&
					    pi->sh->chippkg == BCMA_PKG_ID_BCM43224_FAB_SMIC) {
						bias = 0x2a;
						cascbias = 0x38;
					}

					pag_boost_tune = 0x4;
					pgag_boost_tune = 0x03;
					padg_boost_tune = 0x77;
					mixg_boost_tune = 0x65;
				}

				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_IMAIN_STAT, bias);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_IAUX_STAT, bias);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_CASCBIAS, cascbias);

				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_BOOST_TUNE,
						 pag_boost_tune);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 PGAG_BOOST_TUNE,
						 pgag_boost_tune);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 PADG_BOOST_TUNE,
						 padg_boost_tune);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 MIXG_BOOST_TUNE,
						 mixg_boost_tune);
			} else {

				bias = (pi->bw == WL_CHANSPEC_BW_40) ?
				       0x40 : 0x20;

				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_IMAIN_STAT, bias);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_IAUX_STAT, bias);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 INTPAG_CASCBIAS, 0x30);
			}
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, PA_SPARE1,
					 0xee);
		}
	}

	if (PHY_IPA(pi) && NREV_IS(pi->pubpi.phy_rev, 6)
	    && CHSPEC_IS5G(pi->radio_chanspec)) {
		u16 paa_boost_tune;
		u16 pada_boost_tune;
		u16 pgaa_boost_tune;
		u16 mixa_boost_tune;
		u16 freq, pabias, cascbias;
		uint core;

		freq = CHAN5G_FREQ(CHSPEC_CHANNEL(pi->radio_chanspec));

		if (freq < 5150) {

			paa_boost_tune = 0xa;
			pada_boost_tune = 0x77;
			pgaa_boost_tune = 0xf;
			mixa_boost_tune = 0xf;
		} else if (freq < 5340) {

			paa_boost_tune = 0x8;
			pada_boost_tune = 0x77;
			pgaa_boost_tune = 0xfb;
			mixa_boost_tune = 0xf;
		} else if (freq < 5650) {

			paa_boost_tune = 0x0;
			pada_boost_tune = 0x77;
			pgaa_boost_tune = 0xb;
			mixa_boost_tune = 0xf;
		} else {

			paa_boost_tune = 0x0;
			pada_boost_tune = 0x77;
			if (freq != 5825)
				pgaa_boost_tune = -(int)(freq - 18) / 36 + 168;
			else
				pgaa_boost_tune = 6;

			mixa_boost_tune = 0xf;
		}

		for (core = 0; core < pi->pubpi.phy_corenum; core++) {
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAA_BOOST_TUNE, paa_boost_tune);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 PADA_BOOST_TUNE, pada_boost_tune);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 PGAA_BOOST_TUNE, pgaa_boost_tune);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 MIXA_BOOST_TUNE, mixa_boost_tune);

			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 TXSPARE1, 0x30);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 PA_SPARE2, 0xee);

			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 PADA_CASCBIAS, 0x3);

			cascbias = 0x30;

			if ((pi->sh->chip == BCMA_CHIP_ID_BCM43224 ||
			     pi->sh->chip == BCMA_CHIP_ID_BCM43225) &&
			    pi->sh->chippkg == BCMA_PKG_ID_BCM43224_FAB_SMIC)
				cascbias = 0x35;

			pabias = (pi->phy_pabias == 0) ? 0x30 : pi->phy_pabias;

			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAA_IAUX_STAT, pabias);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAA_IMAIN_STAT, pabias);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAA_CASCBIAS, cascbias);
		}
	}

	udelay(50);

	wlc_phy_radio205x_vcocal_nphy(pi);
}