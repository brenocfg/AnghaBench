#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_8__ {int radiorev; int phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct TYPE_6__ {int triso; } ;
struct TYPE_5__ {int triso; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_4__ pubpi; scalar_t__ nphy_elna_gain_config; scalar_t__ nphy_gain_boost; TYPE_3__* sh; TYPE_2__ srom_fem2g; TYPE_1__ srom_fem5g; } ;
typedef  int s8 ;
struct TYPE_7__ {int boardflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int BFL_EXTLNA ; 
 int BFL_EXTLNA_5GHz ; 
 int BPHY_OPTIONAL_MODES ; 
 scalar_t__ CHSPEC_IS20 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int NPHY_BandControl_currentBand ; 
 int NPHY_RFSEQ_CMD_CLR_HIQ_DIS ; 
 int NPHY_RFSEQ_CMD_RX_GAIN ; 
 int NPHY_RFSEQ_CMD_SET_HPF_BW ; 
 int /*<<< orphan*/  NPHY_RFSEQ_UPDATEGAINU ; 
 int NPHY_RSSICAL_W1_TARGET ; 
 int NPHY_TBL_ID_GAIN1 ; 
 int NPHY_TBL_ID_GAIN2 ; 
 int NPHY_TBL_ID_GAINBITS1 ; 
 int NPHY_TBL_ID_GAINBITS2 ; 
 int NPHY_TBL_ID_RFSEQ ; 
 int NPHY_TO_BPHY_OFF ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int RADIO_2056_RX0 ; 
 int RADIO_2056_RX1 ; 
 int RADIO_2056_RX_BIASPOLE_LNAA1_IDAC ; 
 int RADIO_2056_RX_BIASPOLE_LNAG1_IDAC ; 
 int RADIO_2056_RX_LNAA2_IDAC ; 
 int RADIO_2056_RX_LNAG2_IDAC ; 
 int RADIO_2056_RX_RSSI_GAIN ; 
 int RADIO_2056_RX_RSSI_POLE ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_adjust_lnagaintbl_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_set_rfseq_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,...) ; 
 int /*<<< orphan*/  wlc_phy_workarounds_nphy_gainctrl_2057_rev5 (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_workarounds_nphy_gainctrl_2057_rev6 (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_workarounds_nphy_gainctrl(struct brcms_phy *pi)
{
	u16 w1th, hpf_code, currband;
	int ctr;
	u8 rfseq_updategainu_events[] = {
		NPHY_RFSEQ_CMD_RX_GAIN,
		NPHY_RFSEQ_CMD_CLR_HIQ_DIS,
		NPHY_RFSEQ_CMD_SET_HPF_BW
	};
	static const u8 rfseq_updategainu_dlys[] = { 10, 30, 1 };
	static const s8 lna1G_gain_db[] = { 7, 11, 16, 23 };
	static const s8 lna1G_gain_db_rev4[] = { 8, 12, 17, 25 };
	static const s8 lna1G_gain_db_rev5[] = { 9, 13, 18, 26 };
	static const s8 lna1G_gain_db_rev6[] = { 8, 13, 18, 25 };
	static const s8 lna1G_gain_db_rev6_224B0[] = { 10, 14, 19, 27 };
	static const s8 lna1A_gain_db[] = { 7, 11, 17, 23 };
	static const s8 lna1A_gain_db_rev4[] = { 8, 12, 18, 23 };
	static const s8 lna1A_gain_db_rev5[] = { 6, 10, 16, 21 };
	static const s8 lna1A_gain_db_rev6[] = { 6, 10, 16, 21 };
	const s8 *lna1_gain_db = NULL;
	static const s8 lna2G_gain_db[] = { -5, 6, 10, 14 };
	static const s8 lna2G_gain_db_rev5[] = { -3, 7, 11, 16 };
	static const s8 lna2G_gain_db_rev6[] = { -5, 6, 10, 14 };
	static const s8 lna2G_gain_db_rev6_224B0[] = { -5, 6, 10, 15 };
	static const s8 lna2A_gain_db[] = { -6, 2, 6, 10 };
	static const s8 lna2A_gain_db_rev4[] = { -5, 2, 6, 10 };
	static const s8 lna2A_gain_db_rev5[] = { -7, 0, 4, 8 };
	static const s8 lna2A_gain_db_rev6[] = { -7, 0, 4, 8 };
	const s8 *lna2_gain_db = NULL;
	static const s8 tiaG_gain_db[] = {
		0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
	static const s8 tiaA_gain_db[] = {
		0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13 };
	static const s8 tiaA_gain_db_rev4[] = {
		0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d };
	static const s8 tiaA_gain_db_rev5[] = {
		0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d };
	static const s8 tiaA_gain_db_rev6[] = {
		0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d };
	const s8 *tia_gain_db;
	static const s8 tiaG_gainbits[] = {
		0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 };
	static const s8 tiaA_gainbits[] = {
		0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 };
	static const s8 tiaA_gainbits_rev4[] = {
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
	static const s8 tiaA_gainbits_rev5[] = {
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
	static const s8 tiaA_gainbits_rev6[] = {
		0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
	const s8 *tia_gainbits;
	static const s8 lpf_gain_db[] = { 0x00, 0x06, 0x0c, 0x12, 0x12, 0x12 };
	static const s8 lpf_gainbits[] = { 0x00, 0x01, 0x02, 0x03, 0x03, 0x03 };
	static const u16 rfseqG_init_gain[] = { 0x613f, 0x613f, 0x613f, 0x613f };
	static const u16 rfseqG_init_gain_rev4[] = { 0x513f, 0x513f, 0x513f, 0x513f };
	static const u16 rfseqG_init_gain_rev5[] = { 0x413f, 0x413f, 0x413f, 0x413f };
	static const u16 rfseqG_init_gain_rev5_elna[] = {
		0x013f, 0x013f, 0x013f, 0x013f };
	static const u16 rfseqG_init_gain_rev6[] = { 0x513f, 0x513f };
	static const u16 rfseqG_init_gain_rev6_224B0[] = { 0x413f, 0x413f };
	static const u16 rfseqG_init_gain_rev6_elna[] = { 0x113f, 0x113f };
	static const u16 rfseqA_init_gain[] = { 0x516f, 0x516f, 0x516f, 0x516f };
	static const u16 rfseqA_init_gain_rev4[] = { 0x614f, 0x614f, 0x614f, 0x614f };
	static const u16 rfseqA_init_gain_rev4_elna[] = {
		0x314f, 0x314f, 0x314f, 0x314f };
	static const u16 rfseqA_init_gain_rev5[] = { 0x714f, 0x714f, 0x714f, 0x714f };
	static const u16 rfseqA_init_gain_rev6[] = { 0x714f, 0x714f };
	const u16 *rfseq_init_gain;
	u16 initG_gaincode = 0x627e;
	u16 initG_gaincode_rev4 = 0x527e;
	u16 initG_gaincode_rev5 = 0x427e;
	u16 initG_gaincode_rev5_elna = 0x027e;
	u16 initG_gaincode_rev6 = 0x527e;
	u16 initG_gaincode_rev6_224B0 = 0x427e;
	u16 initG_gaincode_rev6_elna = 0x127e;
	u16 initA_gaincode = 0x52de;
	u16 initA_gaincode_rev4 = 0x629e;
	u16 initA_gaincode_rev4_elna = 0x329e;
	u16 initA_gaincode_rev5 = 0x729e;
	u16 initA_gaincode_rev6 = 0x729e;
	u16 init_gaincode;
	u16 clip1hiG_gaincode = 0x107e;
	u16 clip1hiG_gaincode_rev4 = 0x007e;
	u16 clip1hiG_gaincode_rev5 = 0x1076;
	u16 clip1hiG_gaincode_rev6 = 0x007e;
	u16 clip1hiA_gaincode = 0x00de;
	u16 clip1hiA_gaincode_rev4 = 0x029e;
	u16 clip1hiA_gaincode_rev5 = 0x029e;
	u16 clip1hiA_gaincode_rev6 = 0x029e;
	u16 clip1hi_gaincode;
	u16 clip1mdG_gaincode = 0x0066;
	u16 clip1mdA_gaincode = 0x00ca;
	u16 clip1mdA_gaincode_rev4 = 0x1084;
	u16 clip1mdA_gaincode_rev5 = 0x2084;
	u16 clip1mdA_gaincode_rev6 = 0x2084;
	u16 clip1md_gaincode = 0;
	u16 clip1loG_gaincode = 0x0074;
	static const u16 clip1loG_gaincode_rev5[] = {
		0x0062, 0x0064, 0x006a, 0x106a, 0x106c, 0x1074, 0x107c, 0x207c
	};
	static const u16 clip1loG_gaincode_rev6[] = {
		0x106a, 0x106c, 0x1074, 0x107c, 0x007e, 0x107e, 0x207e, 0x307e
	};
	u16 clip1loG_gaincode_rev6_224B0 = 0x1074;
	u16 clip1loA_gaincode = 0x00cc;
	u16 clip1loA_gaincode_rev4 = 0x0086;
	u16 clip1loA_gaincode_rev5 = 0x2086;
	u16 clip1loA_gaincode_rev6 = 0x2086;
	u16 clip1lo_gaincode;
	u8 crsminG_th = 0x18;
	u8 crsminG_th_rev5 = 0x18;
	u8 crsminG_th_rev6 = 0x18;
	u8 crsminA_th = 0x1e;
	u8 crsminA_th_rev4 = 0x24;
	u8 crsminA_th_rev5 = 0x24;
	u8 crsminA_th_rev6 = 0x24;
	u8 crsmin_th;
	u8 crsminlG_th = 0x18;
	u8 crsminlG_th_rev5 = 0x18;
	u8 crsminlG_th_rev6 = 0x18;
	u8 crsminlA_th = 0x1e;
	u8 crsminlA_th_rev4 = 0x24;
	u8 crsminlA_th_rev5 = 0x24;
	u8 crsminlA_th_rev6 = 0x24;
	u8 crsminl_th = 0;
	u8 crsminuG_th = 0x18;
	u8 crsminuG_th_rev5 = 0x18;
	u8 crsminuG_th_rev6 = 0x18;
	u8 crsminuA_th = 0x1e;
	u8 crsminuA_th_rev4 = 0x24;
	u8 crsminuA_th_rev5 = 0x24;
	u8 crsminuA_th_rev6 = 0x24;
	u8 crsminuA_th_rev6_224B0 = 0x2d;
	u8 crsminu_th;
	u16 nbclipG_th = 0x20d;
	u16 nbclipG_th_rev4 = 0x1a1;
	u16 nbclipG_th_rev5 = 0x1d0;
	u16 nbclipG_th_rev6 = 0x1d0;
	u16 nbclipA_th = 0x1a1;
	u16 nbclipA_th_rev4 = 0x107;
	u16 nbclipA_th_rev5 = 0x0a9;
	u16 nbclipA_th_rev6 = 0x0f0;
	u16 nbclip_th = 0;
	u8 w1clipG_th = 5;
	u8 w1clipG_th_rev5 = 9;
	u8 w1clipG_th_rev6 = 5;
	u8 w1clipA_th = 25, w1clip_th;
	u8 rssi_gain_default = 0x50;
	u8 rssiG_gain_rev6_224B0 = 0x50;
	u8 rssiA_gain_rev5 = 0x90;
	u8 rssiA_gain_rev6 = 0x90;
	u8 rssi_gain;
	u16 regval[21];
	u8 triso;

	triso = (CHSPEC_IS5G(pi->radio_chanspec)) ? pi->srom_fem5g.triso :
		pi->srom_fem2g.triso;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		if (pi->pubpi.radiorev == 5) {
			wlc_phy_workarounds_nphy_gainctrl_2057_rev5(pi);
		} else if (pi->pubpi.radiorev == 7) {
			wlc_phy_workarounds_nphy_gainctrl_2057_rev6(pi);

			mod_phy_reg(pi, 0x283, (0xff << 0), (0x44 << 0));
			mod_phy_reg(pi, 0x280, (0xff << 0), (0x44 << 0));

		} else if ((pi->pubpi.radiorev == 3)
			   || (pi->pubpi.radiorev == 8)) {
			wlc_phy_workarounds_nphy_gainctrl_2057_rev6(pi);

			if (pi->pubpi.radiorev == 8) {
				mod_phy_reg(pi, 0x283,
					    (0xff << 0), (0x44 << 0));
				mod_phy_reg(pi, 0x280,
					    (0xff << 0), (0x44 << 0));
			}
		} else {
			wlc_phy_workarounds_nphy_gainctrl_2057_rev6(pi);
		}
	} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {

		mod_phy_reg(pi, 0xa0, (0x1 << 6), (1 << 6));

		mod_phy_reg(pi, 0x1c, (0x1 << 13), (1 << 13));
		mod_phy_reg(pi, 0x32, (0x1 << 13), (1 << 13));

		currband =
			read_phy_reg(pi, 0x09) & NPHY_BandControl_currentBand;
		if (currband == 0) {
			if (NREV_GE(pi->pubpi.phy_rev, 6)) {
				if (pi->pubpi.radiorev == 11) {
					lna1_gain_db = lna1G_gain_db_rev6_224B0;
					lna2_gain_db = lna2G_gain_db_rev6_224B0;
					rfseq_init_gain =
						rfseqG_init_gain_rev6_224B0;
					init_gaincode =
						initG_gaincode_rev6_224B0;
					clip1hi_gaincode =
						clip1hiG_gaincode_rev6;
					clip1lo_gaincode =
						clip1loG_gaincode_rev6_224B0;
					nbclip_th = nbclipG_th_rev6;
					w1clip_th = w1clipG_th_rev6;
					crsmin_th = crsminG_th_rev6;
					crsminl_th = crsminlG_th_rev6;
					crsminu_th = crsminuG_th_rev6;
					rssi_gain = rssiG_gain_rev6_224B0;
				} else {
					lna1_gain_db = lna1G_gain_db_rev6;
					lna2_gain_db = lna2G_gain_db_rev6;
					if (pi->sh->boardflags & BFL_EXTLNA) {

						rfseq_init_gain =
						     rfseqG_init_gain_rev6_elna;
						init_gaincode =
						       initG_gaincode_rev6_elna;
					} else {
						rfseq_init_gain =
							rfseqG_init_gain_rev6;
						init_gaincode =
							initG_gaincode_rev6;
					}
					clip1hi_gaincode =
						clip1hiG_gaincode_rev6;
					switch (triso) {
					case 0:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[0];
						break;
					case 1:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[1];
						break;
					case 2:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[2];
						break;
					case 3:
					default:

						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[3];
						break;
					case 4:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[4];
						break;
					case 5:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[5];
						break;
					case 6:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[6];
						break;
					case 7:
						clip1lo_gaincode =
							clip1loG_gaincode_rev6
							[7];
						break;
					}
					nbclip_th = nbclipG_th_rev6;
					w1clip_th = w1clipG_th_rev6;
					crsmin_th = crsminG_th_rev6;
					crsminl_th = crsminlG_th_rev6;
					crsminu_th = crsminuG_th_rev6;
					rssi_gain = rssi_gain_default;
				}
			} else if (NREV_IS(pi->pubpi.phy_rev, 5)) {
				lna1_gain_db = lna1G_gain_db_rev5;
				lna2_gain_db = lna2G_gain_db_rev5;
				if (pi->sh->boardflags & BFL_EXTLNA) {

					rfseq_init_gain =
						rfseqG_init_gain_rev5_elna;
					init_gaincode =
						initG_gaincode_rev5_elna;
				} else {
					rfseq_init_gain = rfseqG_init_gain_rev5;
					init_gaincode = initG_gaincode_rev5;
				}
				clip1hi_gaincode = clip1hiG_gaincode_rev5;
				switch (triso) {
				case 0:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[0];
					break;
				case 1:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[1];
					break;
				case 2:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[2];
					break;
				case 3:

					clip1lo_gaincode =
						clip1loG_gaincode_rev5[3];
					break;
				case 4:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[4];
					break;
				case 5:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[5];
					break;
				case 6:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[6];
					break;
				case 7:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[7];
					break;
				default:
					clip1lo_gaincode =
						clip1loG_gaincode_rev5[3];
					break;
				}
				nbclip_th = nbclipG_th_rev5;
				w1clip_th = w1clipG_th_rev5;
				crsmin_th = crsminG_th_rev5;
				crsminl_th = crsminlG_th_rev5;
				crsminu_th = crsminuG_th_rev5;
				rssi_gain = rssi_gain_default;
			} else if (NREV_IS(pi->pubpi.phy_rev, 4)) {
				lna1_gain_db = lna1G_gain_db_rev4;
				lna2_gain_db = lna2G_gain_db;
				rfseq_init_gain = rfseqG_init_gain_rev4;
				init_gaincode = initG_gaincode_rev4;
				clip1hi_gaincode = clip1hiG_gaincode_rev4;
				clip1lo_gaincode = clip1loG_gaincode;
				nbclip_th = nbclipG_th_rev4;
				w1clip_th = w1clipG_th;
				crsmin_th = crsminG_th;
				crsminl_th = crsminlG_th;
				crsminu_th = crsminuG_th;
				rssi_gain = rssi_gain_default;
			} else {
				lna1_gain_db = lna1G_gain_db;
				lna2_gain_db = lna2G_gain_db;
				rfseq_init_gain = rfseqG_init_gain;
				init_gaincode = initG_gaincode;
				clip1hi_gaincode = clip1hiG_gaincode;
				clip1lo_gaincode = clip1loG_gaincode;
				nbclip_th = nbclipG_th;
				w1clip_th = w1clipG_th;
				crsmin_th = crsminG_th;
				crsminl_th = crsminlG_th;
				crsminu_th = crsminuG_th;
				rssi_gain = rssi_gain_default;
			}
			tia_gain_db = tiaG_gain_db;
			tia_gainbits = tiaG_gainbits;
			clip1md_gaincode = clip1mdG_gaincode;
		} else {
			if (NREV_GE(pi->pubpi.phy_rev, 6)) {
				lna1_gain_db = lna1A_gain_db_rev6;
				lna2_gain_db = lna2A_gain_db_rev6;
				tia_gain_db = tiaA_gain_db_rev6;
				tia_gainbits = tiaA_gainbits_rev6;
				rfseq_init_gain = rfseqA_init_gain_rev6;
				init_gaincode = initA_gaincode_rev6;
				clip1hi_gaincode = clip1hiA_gaincode_rev6;
				clip1md_gaincode = clip1mdA_gaincode_rev6;
				clip1lo_gaincode = clip1loA_gaincode_rev6;
				crsmin_th = crsminA_th_rev6;
				crsminl_th = crsminlA_th_rev6;
				if ((pi->pubpi.radiorev == 11) &&
				    (CHSPEC_IS40(pi->radio_chanspec) == 0))
					crsminu_th = crsminuA_th_rev6_224B0;
				else
					crsminu_th = crsminuA_th_rev6;

				nbclip_th = nbclipA_th_rev6;
				rssi_gain = rssiA_gain_rev6;
			} else if (NREV_IS(pi->pubpi.phy_rev, 5)) {
				lna1_gain_db = lna1A_gain_db_rev5;
				lna2_gain_db = lna2A_gain_db_rev5;
				tia_gain_db = tiaA_gain_db_rev5;
				tia_gainbits = tiaA_gainbits_rev5;
				rfseq_init_gain = rfseqA_init_gain_rev5;
				init_gaincode = initA_gaincode_rev5;
				clip1hi_gaincode = clip1hiA_gaincode_rev5;
				clip1md_gaincode = clip1mdA_gaincode_rev5;
				clip1lo_gaincode = clip1loA_gaincode_rev5;
				crsmin_th = crsminA_th_rev5;
				crsminl_th = crsminlA_th_rev5;
				crsminu_th = crsminuA_th_rev5;
				nbclip_th = nbclipA_th_rev5;
				rssi_gain = rssiA_gain_rev5;
			} else if (NREV_IS(pi->pubpi.phy_rev, 4)) {
				lna1_gain_db = lna1A_gain_db_rev4;
				lna2_gain_db = lna2A_gain_db_rev4;
				tia_gain_db = tiaA_gain_db_rev4;
				tia_gainbits = tiaA_gainbits_rev4;
				if (pi->sh->boardflags & BFL_EXTLNA_5GHz) {

					rfseq_init_gain =
						rfseqA_init_gain_rev4_elna;
					init_gaincode =
						initA_gaincode_rev4_elna;
				} else {
					rfseq_init_gain = rfseqA_init_gain_rev4;
					init_gaincode = initA_gaincode_rev4;
				}
				clip1hi_gaincode = clip1hiA_gaincode_rev4;
				clip1md_gaincode = clip1mdA_gaincode_rev4;
				clip1lo_gaincode = clip1loA_gaincode_rev4;
				crsmin_th = crsminA_th_rev4;
				crsminl_th = crsminlA_th_rev4;
				crsminu_th = crsminuA_th_rev4;
				nbclip_th = nbclipA_th_rev4;
				rssi_gain = rssi_gain_default;
			} else {
				lna1_gain_db = lna1A_gain_db;
				lna2_gain_db = lna2A_gain_db;
				tia_gain_db = tiaA_gain_db;
				tia_gainbits = tiaA_gainbits;
				rfseq_init_gain = rfseqA_init_gain;
				init_gaincode = initA_gaincode;
				clip1hi_gaincode = clip1hiA_gaincode;
				clip1md_gaincode = clip1mdA_gaincode;
				clip1lo_gaincode = clip1loA_gaincode;
				crsmin_th = crsminA_th;
				crsminl_th = crsminlA_th;
				crsminu_th = crsminuA_th;
				nbclip_th = nbclipA_th;
				rssi_gain = rssi_gain_default;
			}
			w1clip_th = w1clipA_th;
		}

		write_radio_reg(pi,
				(RADIO_2056_RX_BIASPOLE_LNAG1_IDAC |
				 RADIO_2056_RX0), 0x17);
		write_radio_reg(pi,
				(RADIO_2056_RX_BIASPOLE_LNAG1_IDAC |
				 RADIO_2056_RX1), 0x17);

		write_radio_reg(pi, (RADIO_2056_RX_LNAG2_IDAC | RADIO_2056_RX0),
				0xf0);
		write_radio_reg(pi, (RADIO_2056_RX_LNAG2_IDAC | RADIO_2056_RX1),
				0xf0);

		write_radio_reg(pi, (RADIO_2056_RX_RSSI_POLE | RADIO_2056_RX0),
				0x0);
		write_radio_reg(pi, (RADIO_2056_RX_RSSI_POLE | RADIO_2056_RX1),
				0x0);

		write_radio_reg(pi, (RADIO_2056_RX_RSSI_GAIN | RADIO_2056_RX0),
				rssi_gain);
		write_radio_reg(pi, (RADIO_2056_RX_RSSI_GAIN | RADIO_2056_RX1),
				rssi_gain);

		write_radio_reg(pi,
				(RADIO_2056_RX_BIASPOLE_LNAA1_IDAC |
				 RADIO_2056_RX0), 0x17);
		write_radio_reg(pi,
				(RADIO_2056_RX_BIASPOLE_LNAA1_IDAC |
				 RADIO_2056_RX1), 0x17);

		write_radio_reg(pi, (RADIO_2056_RX_LNAA2_IDAC | RADIO_2056_RX0),
				0xFF);
		write_radio_reg(pi, (RADIO_2056_RX_LNAA2_IDAC | RADIO_2056_RX1),
				0xFF);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 8,
					 8, lna1_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 8,
					 8, lna1_gain_db);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 0x10,
					 8, lna2_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 0x10,
					 8, lna2_gain_db);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 10, 0x20,
					 8, tia_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 10, 0x20,
					 8, tia_gain_db);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS1, 10, 0x20,
					 8, tia_gainbits);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS2, 10, 0x20,
					 8, tia_gainbits);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 6, 0x40,
					 8, &lpf_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 6, 0x40,
					 8, &lpf_gain_db);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS1, 6, 0x40,
					 8, &lpf_gainbits);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS2, 6, 0x40,
					 8, &lpf_gainbits);

		write_phy_reg(pi, 0x20, init_gaincode);
		write_phy_reg(pi, 0x2a7, init_gaincode);

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ,
					 pi->pubpi.phy_corenum, 0x106, 16,
					 rfseq_init_gain);

		write_phy_reg(pi, 0x22, clip1hi_gaincode);
		write_phy_reg(pi, 0x2a9, clip1hi_gaincode);

		write_phy_reg(pi, 0x24, clip1md_gaincode);
		write_phy_reg(pi, 0x2ab, clip1md_gaincode);

		write_phy_reg(pi, 0x37, clip1lo_gaincode);
		write_phy_reg(pi, 0x2ad, clip1lo_gaincode);

		mod_phy_reg(pi, 0x27d, (0xff << 0), (crsmin_th << 0));
		mod_phy_reg(pi, 0x280, (0xff << 0), (crsminl_th << 0));
		mod_phy_reg(pi, 0x283, (0xff << 0), (crsminu_th << 0));

		write_phy_reg(pi, 0x2b, nbclip_th);
		write_phy_reg(pi, 0x41, nbclip_th);

		mod_phy_reg(pi, 0x27, (0x3f << 0), (w1clip_th << 0));
		mod_phy_reg(pi, 0x3d, (0x3f << 0), (w1clip_th << 0));

		write_phy_reg(pi, 0x150, 0x809c);

	} else {

		mod_phy_reg(pi, 0x1c, (0x1 << 13), (1 << 13));
		mod_phy_reg(pi, 0x32, (0x1 << 13), (1 << 13));

		write_phy_reg(pi, 0x2b, 0x84);
		write_phy_reg(pi, 0x41, 0x84);

		if (CHSPEC_IS20(pi->radio_chanspec)) {
			write_phy_reg(pi, 0x6b, 0x2b);
			write_phy_reg(pi, 0x6c, 0x2b);
			write_phy_reg(pi, 0x6d, 0x9);
			write_phy_reg(pi, 0x6e, 0x9);
		}

		w1th = NPHY_RSSICAL_W1_TARGET - 4;
		mod_phy_reg(pi, 0x27, (0x3f << 0), (w1th << 0));
		mod_phy_reg(pi, 0x3d, (0x3f << 0), (w1th << 0));

		if (CHSPEC_IS20(pi->radio_chanspec)) {
			mod_phy_reg(pi, 0x1c, (0x1f << 0), (0x1 << 0));
			mod_phy_reg(pi, 0x32, (0x1f << 0), (0x1 << 0));

			mod_phy_reg(pi, 0x1d, (0x1f << 0), (0x1 << 0));
			mod_phy_reg(pi, 0x33, (0x1f << 0), (0x1 << 0));
		}

		write_phy_reg(pi, 0x150, 0x809c);

		if (pi->nphy_gain_boost)
			if ((CHSPEC_IS2G(pi->radio_chanspec)) &&
			    (CHSPEC_IS40(pi->radio_chanspec)))
				hpf_code = 4;
			else
				hpf_code = 5;
		else if (CHSPEC_IS40(pi->radio_chanspec))
			hpf_code = 6;
		else
			hpf_code = 7;

		mod_phy_reg(pi, 0x20, (0x1f << 7), (hpf_code << 7));
		mod_phy_reg(pi, 0x36, (0x1f << 7), (hpf_code << 7));

		for (ctr = 0; ctr < 4; ctr++)
			regval[ctr] = (hpf_code << 8) | 0x7c;
		wlc_phy_table_write_nphy(pi, 7, 4, 0x106, 16, regval);

		wlc_phy_adjust_lnagaintbl_nphy(pi);

		if (pi->nphy_elna_gain_config) {
			regval[0] = 0;
			regval[1] = 1;
			regval[2] = 1;
			regval[3] = 1;
			wlc_phy_table_write_nphy(pi, 2, 4, 8, 16, regval);
			wlc_phy_table_write_nphy(pi, 3, 4, 8, 16, regval);

			for (ctr = 0; ctr < 4; ctr++)
				regval[ctr] = (hpf_code << 8) | 0x74;
			wlc_phy_table_write_nphy(pi, 7, 4, 0x106, 16, regval);
		}

		if (NREV_IS(pi->pubpi.phy_rev, 2)) {
			for (ctr = 0; ctr < 21; ctr++)
				regval[ctr] = 3 * ctr;
			wlc_phy_table_write_nphy(pi, 0, 21, 32, 16, regval);
			wlc_phy_table_write_nphy(pi, 1, 21, 32, 16, regval);

			for (ctr = 0; ctr < 21; ctr++)
				regval[ctr] = (u16) ctr;
			wlc_phy_table_write_nphy(pi, 2, 21, 32, 16, regval);
			wlc_phy_table_write_nphy(pi, 3, 21, 32, 16, regval);
		}

		wlc_phy_set_rfseq_nphy(pi, NPHY_RFSEQ_UPDATEGAINU,
				       rfseq_updategainu_events,
				       rfseq_updategainu_dlys,
				       ARRAY_SIZE(rfseq_updategainu_events));

		mod_phy_reg(pi, 0x153, (0xff << 8), (90 << 8));

		if (CHSPEC_IS2G(pi->radio_chanspec))
			mod_phy_reg(pi,
				    (NPHY_TO_BPHY_OFF + BPHY_OPTIONAL_MODES),
				    0x7f, 0x4);
	}
}