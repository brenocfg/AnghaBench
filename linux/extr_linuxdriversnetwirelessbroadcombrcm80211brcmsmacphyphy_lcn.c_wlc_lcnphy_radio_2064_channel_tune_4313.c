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
typedef  size_t uint ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct chan_info_2064_lcnphy {int chan; int const logen_buftune; int logen_rccr_tx; int txrf_mix_tune_ctrl; int pa_input_tune_g; int logen_rccr_rx; int pa_rxrf_lna1_freq_tune; int pa_rxrf_lna2_freq_tune; int const rxrf_rxrf_spare1; int freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int xtalfreq; TYPE_2__* sh; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;
typedef  int s32 ;
struct TYPE_4__ {int boardflags; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct chan_info_2064_lcnphy*) ; 
 int BFL_FEM ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int LCN_BW_LMT ; 
 int LCN_CUR_DIV ; 
 int LCN_CUR_LMT ; 
 int LCN_FACT ; 
 int LCN_MULT ; 
 int LCN_OFFSET ; 
 int LCN_VCO_DIV ; 
 int PLL_2064_D30 ; 
 int PLL_2064_D30_DOUBLER ; 
 int PLL_2064_HIGH_END_KVCO ; 
 int PLL_2064_HIGH_END_VCO ; 
 int PLL_2064_LOOP_BW ; 
 int PLL_2064_LOOP_BW_DOUBLER ; 
 int PLL_2064_LOW_END_KVCO ; 
 int PLL_2064_LOW_END_VCO ; 
 int PLL_2064_MHZ ; 
 int /*<<< orphan*/  RADIO_2064_REG02A ; 
 int /*<<< orphan*/  RADIO_2064_REG030 ; 
 int /*<<< orphan*/  RADIO_2064_REG038 ; 
 int /*<<< orphan*/  RADIO_2064_REG03C ; 
 int /*<<< orphan*/  RADIO_2064_REG03D ; 
 int /*<<< orphan*/  RADIO_2064_REG040 ; 
 int /*<<< orphan*/  RADIO_2064_REG041 ; 
 int /*<<< orphan*/  RADIO_2064_REG042 ; 
 int /*<<< orphan*/  RADIO_2064_REG043 ; 
 int /*<<< orphan*/  RADIO_2064_REG044 ; 
 int /*<<< orphan*/  RADIO_2064_REG045 ; 
 int /*<<< orphan*/  RADIO_2064_REG046 ; 
 int /*<<< orphan*/  RADIO_2064_REG047 ; 
 int /*<<< orphan*/  RADIO_2064_REG048 ; 
 int /*<<< orphan*/  RADIO_2064_REG04F ; 
 int /*<<< orphan*/  RADIO_2064_REG051 ; 
 int /*<<< orphan*/  RADIO_2064_REG052 ; 
 int /*<<< orphan*/  RADIO_2064_REG053 ; 
 int /*<<< orphan*/  RADIO_2064_REG054 ; 
 int /*<<< orphan*/  RADIO_2064_REG05E ; 
 int /*<<< orphan*/  RADIO_2064_REG06C ; 
 int /*<<< orphan*/  RADIO_2064_REG091 ; 
 int /*<<< orphan*/  RADIO_2064_REG09D ; 
 int /*<<< orphan*/  RADIO_2064_REG09E ; 
 int /*<<< orphan*/  RADIO_2064_REG12B ; 
 struct chan_info_2064_lcnphy* chan_info_2064_lcnphy ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  or_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_2064_vco_cal (struct brcms_phy*) ; 
 int wlc_lcnphy_qdiv_roundup (int,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
wlc_lcnphy_radio_2064_channel_tune_4313(struct brcms_phy *pi, u8 channel)
{
	uint i;
	const struct chan_info_2064_lcnphy *ci;
	u8 rfpll_doubler = 0;
	u8 pll_pwrup, pll_pwrup_ovr;
	s32 qFxtal, qFref, qFvco, qFcal;
	u8 d15, d16, f16, e44, e45;
	u32 div_int, div_frac, fvco3, fpfd, fref3, fcal_div;
	u16 loop_bw, d30, setCount;

	u8 h29, h28_ten, e30, h30_ten, cp_current;
	u16 g30, d28;

	ci = &chan_info_2064_lcnphy[0];
	rfpll_doubler = 1;

	mod_radio_reg(pi, RADIO_2064_REG09D, 0x4, 0x1 << 2);

	write_radio_reg(pi, RADIO_2064_REG09E, 0xf);
	if (!rfpll_doubler) {
		loop_bw = PLL_2064_LOOP_BW;
		d30 = PLL_2064_D30;
	} else {
		loop_bw = PLL_2064_LOOP_BW_DOUBLER;
		d30 = PLL_2064_D30_DOUBLER;
	}

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		for (i = 0; i < ARRAY_SIZE(chan_info_2064_lcnphy); i++)
			if (chan_info_2064_lcnphy[i].chan == channel)
				break;

		if (i >= ARRAY_SIZE(chan_info_2064_lcnphy))
			return;

		ci = &chan_info_2064_lcnphy[i];
	}

	write_radio_reg(pi, RADIO_2064_REG02A, ci->logen_buftune);

	mod_radio_reg(pi, RADIO_2064_REG030, 0x3, ci->logen_rccr_tx);

	mod_radio_reg(pi, RADIO_2064_REG091, 0x3, ci->txrf_mix_tune_ctrl);

	mod_radio_reg(pi, RADIO_2064_REG038, 0xf, ci->pa_input_tune_g);

	mod_radio_reg(pi, RADIO_2064_REG030, 0x3 << 2,
		      (ci->logen_rccr_rx) << 2);

	mod_radio_reg(pi, RADIO_2064_REG05E, 0xf, ci->pa_rxrf_lna1_freq_tune);

	mod_radio_reg(pi, RADIO_2064_REG05E, (0xf) << 4,
		      (ci->pa_rxrf_lna2_freq_tune) << 4);

	write_radio_reg(pi, RADIO_2064_REG06C, ci->rxrf_rxrf_spare1);

	pll_pwrup = (u8) read_radio_reg(pi, RADIO_2064_REG044);
	pll_pwrup_ovr = (u8) read_radio_reg(pi, RADIO_2064_REG12B);

	or_radio_reg(pi, RADIO_2064_REG044, 0x07);

	or_radio_reg(pi, RADIO_2064_REG12B, (0x07) << 1);
	e44 = 0;
	e45 = 0;

	fpfd = rfpll_doubler ? (pi->xtalfreq << 1) : (pi->xtalfreq);
	if (pi->xtalfreq > 26000000)
		e44 = 1;
	if (pi->xtalfreq > 52000000)
		e45 = 1;
	if (e44 == 0)
		fcal_div = 1;
	else if (e45 == 0)
		fcal_div = 2;
	else
		fcal_div = 4;
	fvco3 = (ci->freq * 3);
	fref3 = 2 * fpfd;

	qFxtal = wlc_lcnphy_qdiv_roundup(pi->xtalfreq, PLL_2064_MHZ, 16);
	qFref = wlc_lcnphy_qdiv_roundup(fpfd, PLL_2064_MHZ, 16);
	qFcal = pi->xtalfreq * fcal_div / PLL_2064_MHZ;
	qFvco = wlc_lcnphy_qdiv_roundup(fvco3, 2, 16);

	write_radio_reg(pi, RADIO_2064_REG04F, 0x02);

	d15 = (pi->xtalfreq * fcal_div * 4 / 5) / PLL_2064_MHZ - 1;
	write_radio_reg(pi, RADIO_2064_REG052, (0x07 & (d15 >> 2)));
	write_radio_reg(pi, RADIO_2064_REG053, (d15 & 0x3) << 5);

	d16 = (qFcal * 8 / (d15 + 1)) - 1;
	write_radio_reg(pi, RADIO_2064_REG051, d16);

	f16 = ((d16 + 1) * (d15 + 1)) / qFcal;
	setCount = f16 * 3 * (ci->freq) / 32 - 1;
	mod_radio_reg(pi, RADIO_2064_REG053, (0x0f << 0),
		      (u8) (setCount >> 8));

	or_radio_reg(pi, RADIO_2064_REG053, 0x10);
	write_radio_reg(pi, RADIO_2064_REG054, (u8) (setCount & 0xff));

	div_int = ((fvco3 * (PLL_2064_MHZ >> 4)) / fref3) << 4;

	div_frac = ((fvco3 * (PLL_2064_MHZ >> 4)) % fref3) << 4;
	while (div_frac >= fref3) {
		div_int++;
		div_frac -= fref3;
	}
	div_frac = wlc_lcnphy_qdiv_roundup(div_frac, fref3, 20);

	mod_radio_reg(pi, RADIO_2064_REG045, (0x1f << 0),
		      (u8) (div_int >> 4));
	mod_radio_reg(pi, RADIO_2064_REG046, (0x1f << 4),
		      (u8) (div_int << 4));
	mod_radio_reg(pi, RADIO_2064_REG046, (0x0f << 0),
		      (u8) (div_frac >> 16));
	write_radio_reg(pi, RADIO_2064_REG047, (u8) (div_frac >> 8) & 0xff);
	write_radio_reg(pi, RADIO_2064_REG048, (u8) div_frac & 0xff);

	write_radio_reg(pi, RADIO_2064_REG040, 0xfb);

	write_radio_reg(pi, RADIO_2064_REG041, 0x9A);
	write_radio_reg(pi, RADIO_2064_REG042, 0xA3);
	write_radio_reg(pi, RADIO_2064_REG043, 0x0C);

	h29 = LCN_BW_LMT / loop_bw;
	d28 = (((PLL_2064_HIGH_END_KVCO - PLL_2064_LOW_END_KVCO) *
		(fvco3 / 2 - PLL_2064_LOW_END_VCO)) /
	       (PLL_2064_HIGH_END_VCO - PLL_2064_LOW_END_VCO))
	      + PLL_2064_LOW_END_KVCO;
	h28_ten = (d28 * 10) / LCN_VCO_DIV;
	e30 = (d30 - LCN_OFFSET) / LCN_FACT;
	g30 = LCN_OFFSET + (e30 * LCN_FACT);
	h30_ten = (g30 * 10) / LCN_CUR_DIV;
	cp_current = ((LCN_CUR_LMT * h29 * LCN_MULT * 100) / h28_ten) / h30_ten;
	mod_radio_reg(pi, RADIO_2064_REG03C, 0x3f, cp_current);

	if (channel >= 1 && channel <= 5)
		write_radio_reg(pi, RADIO_2064_REG03C, 0x8);
	else
		write_radio_reg(pi, RADIO_2064_REG03C, 0x7);
	write_radio_reg(pi, RADIO_2064_REG03D, 0x3);

	mod_radio_reg(pi, RADIO_2064_REG044, 0x0c, 0x0c);
	udelay(1);

	wlc_2064_vco_cal(pi);

	write_radio_reg(pi, RADIO_2064_REG044, pll_pwrup);
	write_radio_reg(pi, RADIO_2064_REG12B, pll_pwrup_ovr);
	if (LCNREV_IS(pi->pubpi.phy_rev, 1)) {
		write_radio_reg(pi, RADIO_2064_REG038, 3);
		write_radio_reg(pi, RADIO_2064_REG091, 7);
	}

	if (!(pi->sh->boardflags & BFL_FEM)) {
		static const u8 reg038[14] = {
			0xd, 0xe, 0xd, 0xd, 0xd, 0xc, 0xa,
			0xb, 0xb, 0x3, 0x3, 0x2, 0x0, 0x0
		};

		write_radio_reg(pi, RADIO_2064_REG02A, 0xf);
		write_radio_reg(pi, RADIO_2064_REG091, 0x3);
		write_radio_reg(pi, RADIO_2064_REG038, 0x3);

		write_radio_reg(pi, RADIO_2064_REG038, reg038[channel - 1]);
	}
}