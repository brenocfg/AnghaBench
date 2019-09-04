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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int nphy_sample_play_lpf_bw_ctl_ovr; int nphy_bb_mult_save; scalar_t__ phyhang_avoid; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 int BB_MULT_MASK ; 
 int BB_MULT_VALID_MASK ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int NPHY_RfseqMode_CoreActv_override ; 
 int /*<<< orphan*/  NPHY_TBL_ID_IQLOCAL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_read_lpf_bw_ctl_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_runsamples_nphy(struct brcms_phy *pi, u16 num_samps, u16 loops,
			u16 wait, u8 iqmode, u8 dac_test_mode,
			bool modify_bbmult)
{
	u16 bb_mult;
	u8 phy_bw, sample_cmd;
	u16 orig_RfseqCoreActv;
	u16 lpf_bw_ctl_override3, lpf_bw_ctl_override4, lpf_bw_ctl_miscreg3,
	    lpf_bw_ctl_miscreg4;

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	phy_bw = 20;
	if (CHSPEC_IS40(pi->radio_chanspec))
		phy_bw = 40;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		lpf_bw_ctl_override3 = read_phy_reg(pi, 0x342) & (0x1 << 7);
		lpf_bw_ctl_override4 = read_phy_reg(pi, 0x343) & (0x1 << 7);
		if (lpf_bw_ctl_override3 | lpf_bw_ctl_override4) {
			lpf_bw_ctl_miscreg3 = read_phy_reg(pi, 0x340) &
					      (0x7 << 8);
			lpf_bw_ctl_miscreg4 = read_phy_reg(pi, 0x341) &
					      (0x7 << 8);
		} else {
			wlc_phy_rfctrl_override_nphy_rev7(
				pi,
				(0x1 << 7),
				wlc_phy_read_lpf_bw_ctl_nphy
					(pi,
					0), 0, 0,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);

			pi->nphy_sample_play_lpf_bw_ctl_ovr = true;

			lpf_bw_ctl_miscreg3 = read_phy_reg(pi, 0x340) &
					      (0x7 << 8);
			lpf_bw_ctl_miscreg4 = read_phy_reg(pi, 0x341) &
					      (0x7 << 8);
		}
	}

	if ((pi->nphy_bb_mult_save & BB_MULT_VALID_MASK) == 0) {

		wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL, 1, 87, 16,
					&bb_mult);
		pi->nphy_bb_mult_save =
			BB_MULT_VALID_MASK | (bb_mult & BB_MULT_MASK);
	}

	if (modify_bbmult) {
		bb_mult = (phy_bw == 20) ? 100 : 71;
		bb_mult = (bb_mult << 8) + bb_mult;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 1, 87, 16,
					 &bb_mult);
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);

	write_phy_reg(pi, 0xc6, num_samps - 1);

	if (loops != 0xffff)
		write_phy_reg(pi, 0xc4, loops - 1);
	else
		write_phy_reg(pi, 0xc4, loops);

	write_phy_reg(pi, 0xc5, wait);

	orig_RfseqCoreActv = read_phy_reg(pi, 0xa1);
	or_phy_reg(pi, 0xa1, NPHY_RfseqMode_CoreActv_override);
	if (iqmode) {

		and_phy_reg(pi, 0xc2, 0x7FFF);

		or_phy_reg(pi, 0xc2, 0x8000);
	} else {

		sample_cmd = (dac_test_mode == 1) ? 0x5 : 0x1;
		write_phy_reg(pi, 0xc3, sample_cmd);
	}

	SPINWAIT(((read_phy_reg(pi, 0xa4) & 0x1) == 1), 1000);

	write_phy_reg(pi, 0xa1, orig_RfseqCoreActv);
}