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
struct TYPE_2__ {int phy_corenum; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;
typedef  int s8 ;

/* Variables and functions */
 int CHAN5G_FREQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS20 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int NPHY_BandControl_currentBand ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAIN1 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAIN2 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAINBITS1 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAINBITS2 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_RFSEQ ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int const*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_workarounds_nphy_gainctrl_2057_rev6(struct brcms_phy *pi)
{
	u16 currband;
	static const s8 lna1G_gain_db_rev7[] = { 9, 14, 19, 24 };
	const s8 *lna1_gain_db = NULL;
	const s8 *lna1_gain_db_2 = NULL;
	const s8 *lna2_gain_db = NULL;
	static const s8 tiaA_gain_db_rev7[] = { -9, -6, -3, 0, 3, 3, 3, 3, 3, 3 };
	const s8 *tia_gain_db;
	static const s8 tiaA_gainbits_rev7[] = { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4 };
	const s8 *tia_gainbits;
	static const u16 rfseqA_init_gain_rev7[] = { 0x624f, 0x624f };
	const u16 *rfseq_init_gain;
	u16 init_gaincode;
	u16 clip1hi_gaincode;
	u16 clip1md_gaincode = 0;
	u16 clip1md_gaincode_B;
	u16 clip1lo_gaincode;
	u16 clip1lo_gaincode_B;
	u8 crsminl_th = 0;
	u8 crsminu_th;
	u16 nbclip_th = 0;
	u8 w1clip_th;
	u16 freq;
	s8 nvar_baseline_offset0 = 0, nvar_baseline_offset1 = 0;
	u8 chg_nbclip_th = 0;

	mod_phy_reg(pi, 0x1c, (0x1 << 13), (1 << 13));
	mod_phy_reg(pi, 0x32, (0x1 << 13), (1 << 13));

	currband = read_phy_reg(pi, 0x09) & NPHY_BandControl_currentBand;
	if (currband == 0) {

		lna1_gain_db = lna1G_gain_db_rev7;

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 8, 8,
					 lna1_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 8, 8,
					 lna1_gain_db);

		mod_phy_reg(pi, 0x283, (0xff << 0), (0x40 << 0));

		if (CHSPEC_IS40(pi->radio_chanspec)) {
			mod_phy_reg(pi, 0x280, (0xff << 0), (0x3e << 0));
			mod_phy_reg(pi, 0x283, (0xff << 0), (0x3e << 0));
		}

		mod_phy_reg(pi, 0x289, (0xff << 0), (0x46 << 0));

		if (CHSPEC_IS20(pi->radio_chanspec)) {
			mod_phy_reg(pi, 0x300, (0x3f << 0), (13 << 0));
			mod_phy_reg(pi, 0x301, (0x3f << 0), (13 << 0));
		}
	} else {

		init_gaincode = 0x9e;
		clip1hi_gaincode = 0x9e;
		clip1md_gaincode_B = 0x24;
		clip1lo_gaincode = 0x8a;
		clip1lo_gaincode_B = 8;
		rfseq_init_gain = rfseqA_init_gain_rev7;

		tia_gain_db = tiaA_gain_db_rev7;
		tia_gainbits = tiaA_gainbits_rev7;

		freq = CHAN5G_FREQ(CHSPEC_CHANNEL(pi->radio_chanspec));
		if (CHSPEC_IS20(pi->radio_chanspec)) {

			w1clip_th = 25;
			clip1md_gaincode = 0x82;

			if ((freq <= 5080) || (freq == 5825)) {

				static const s8 lna1A_gain_db_rev7[] = { 11, 16, 20, 24 };
				static const s8 lna1A_gain_db_2_rev7[] = { 11, 17, 22, 25};
				static const s8 lna2A_gain_db_rev7[] = { -1, 6, 10, 14 };

				crsminu_th = 0x3e;
				lna1_gain_db = lna1A_gain_db_rev7;
				lna1_gain_db_2 = lna1A_gain_db_2_rev7;
				lna2_gain_db = lna2A_gain_db_rev7;
			} else if ((freq >= 5500) && (freq <= 5700)) {

				static const s8 lna1A_gain_db_rev7[] = { 11, 17, 21, 25 };
				static const s8 lna1A_gain_db_2_rev7[] = { 12, 18, 22, 26};
				static const s8 lna2A_gain_db_rev7[] = { 1, 8, 12, 16 };

				crsminu_th = 0x45;
				clip1md_gaincode_B = 0x14;
				nbclip_th = 0xff;
				chg_nbclip_th = 1;
				lna1_gain_db = lna1A_gain_db_rev7;
				lna1_gain_db_2 = lna1A_gain_db_2_rev7;
				lna2_gain_db = lna2A_gain_db_rev7;
			} else {

				static const s8 lna1A_gain_db_rev7[] = { 12, 18, 22, 26 };
				static const s8 lna1A_gain_db_2_rev7[] = { 12, 18, 22, 26};
				static const s8 lna2A_gain_db_rev7[] = { -1, 6, 10, 14 };

				crsminu_th = 0x41;
				lna1_gain_db = lna1A_gain_db_rev7;
				lna1_gain_db_2 = lna1A_gain_db_2_rev7;
				lna2_gain_db = lna2A_gain_db_rev7;
			}

			if (freq <= 4920) {
				nvar_baseline_offset0 = 5;
				nvar_baseline_offset1 = 5;
			} else if ((freq > 4920) && (freq <= 5320)) {
				nvar_baseline_offset0 = 3;
				nvar_baseline_offset1 = 5;
			} else if ((freq > 5320) && (freq <= 5700)) {
				nvar_baseline_offset0 = 3;
				nvar_baseline_offset1 = 2;
			} else {
				nvar_baseline_offset0 = 4;
				nvar_baseline_offset1 = 0;
			}
		} else {

			crsminu_th = 0x3a;
			crsminl_th = 0x3a;
			w1clip_th = 20;

			if ((freq >= 4920) && (freq <= 5320)) {
				nvar_baseline_offset0 = 4;
				nvar_baseline_offset1 = 5;
			} else if ((freq > 5320) && (freq <= 5550)) {
				nvar_baseline_offset0 = 4;
				nvar_baseline_offset1 = 2;
			} else {
				nvar_baseline_offset0 = 5;
				nvar_baseline_offset1 = 3;
			}
		}

		write_phy_reg(pi, 0x20, init_gaincode);
		write_phy_reg(pi, 0x2a7, init_gaincode);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ,
					 pi->pubpi.phy_corenum, 0x106, 16,
					 rfseq_init_gain);

		write_phy_reg(pi, 0x22, clip1hi_gaincode);
		write_phy_reg(pi, 0x2a9, clip1hi_gaincode);

		write_phy_reg(pi, 0x36, clip1md_gaincode_B);
		write_phy_reg(pi, 0x2ac, clip1md_gaincode_B);

		write_phy_reg(pi, 0x37, clip1lo_gaincode);
		write_phy_reg(pi, 0x2ad, clip1lo_gaincode);
		write_phy_reg(pi, 0x38, clip1lo_gaincode_B);
		write_phy_reg(pi, 0x2ae, clip1lo_gaincode_B);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 10, 0x20, 8,
					 tia_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 10, 0x20, 8,
					 tia_gain_db);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS1, 10, 0x20, 8,
					 tia_gainbits);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS2, 10, 0x20, 8,
					 tia_gainbits);

		mod_phy_reg(pi, 0x283, (0xff << 0), (crsminu_th << 0));

		if (chg_nbclip_th == 1) {
			write_phy_reg(pi, 0x2b, nbclip_th);
			write_phy_reg(pi, 0x41, nbclip_th);
		}

		mod_phy_reg(pi, 0x300, (0x3f << 0), (w1clip_th << 0));
		mod_phy_reg(pi, 0x301, (0x3f << 0), (w1clip_th << 0));

		mod_phy_reg(pi, 0x2e4,
			    (0x3f << 0), (nvar_baseline_offset0 << 0));

		mod_phy_reg(pi, 0x2e4,
			    (0x3f << 6), (nvar_baseline_offset1 << 6));

		if (CHSPEC_IS20(pi->radio_chanspec)) {

			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 8, 8,
						 lna1_gain_db);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 8, 8,
						 lna1_gain_db_2);

			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 0x10,
						 8, lna2_gain_db);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 0x10,
						 8, lna2_gain_db);

			write_phy_reg(pi, 0x24, clip1md_gaincode);
			write_phy_reg(pi, 0x2ab, clip1md_gaincode);
		} else {
			mod_phy_reg(pi, 0x280, (0xff << 0), (crsminl_th << 0));
		}
	}
}