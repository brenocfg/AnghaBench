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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct phy_dm_struct {int support_ic_type; scalar_t__* band_width; } ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int MASKBYTE1 ; 
 int MASKBYTE2 ; 
 int MASKBYTE3 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 scalar_t__ ODM_BW20M ; 
 scalar_t__ ODM_BW40M ; 
 scalar_t__ ODM_BW80M ; 
 int ODM_IC_11N_SERIES ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,...) ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydm_bb_debug_info_n_series (struct phy_dm_struct*,int*,char*,int*) ; 

__attribute__((used)) static void phydm_bb_debug_info(void *dm_void, u32 *_used, char *output,
				u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;

	char *tmp_string = NULL;

	u8 rx_ht_bw, rx_vht_bw, rxsc, rx_ht, rx_bw;
	static u8 v_rx_bw;
	u32 value32, value32_1, value32_2, value32_3;
	s32 sfo_a, sfo_b, sfo_c, sfo_d;
	s32 lfo_a, lfo_b, lfo_c, lfo_d;
	static u8 MCSS, tail, parity, rsv, vrsv, idx, smooth, htsound, agg,
		stbc, vstbc, fec, fecext, sgi, sgiext, htltf, vgid, v_nsts,
		vtxops, vrsv2, vbrsv, bf, vbcrc;
	static u16 h_length, htcrc8, length;
	static u16 vpaid;
	static u16 v_length, vhtcrc8, v_mcss, v_tail, vb_tail;
	static u8 hmcss, hrx_bw;

	u8 pwdb;
	s8 rxevm_0, rxevm_1, rxevm_2;
	u8 rf_gain_path_a, rf_gain_path_b, rf_gain_path_c, rf_gain_path_d;
	u8 rx_snr_path_a, rx_snr_path_b, rx_snr_path_c, rx_snr_path_d;
	s32 sig_power;

	const char *L_rate[8] = {"6M",  "9M",  "12M", "18M",
				 "24M", "36M", "48M", "54M"};

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		phydm_bb_debug_info_n_series(dm, &used, output, &out_len);
		return;
	}

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s\n",
		       "BB Report Info");

	/*BW & mode Detection*/

	value32 = odm_get_bb_reg(dm, 0xf80, MASKDWORD);
	value32_2 = value32;
	rx_ht_bw = (u8)(value32 & 0x1);
	rx_vht_bw = (u8)((value32 >> 1) & 0x3);
	rxsc = (u8)(value32 & 0x78);
	value32_1 = (value32 & 0x180) >> 7;
	rx_ht = (u8)(value32_1);

	rx_bw = 0;

	if (rx_ht == 2) {
		if (rx_vht_bw == 0)
			tmp_string = "20M";
		else if (rx_vht_bw == 1)
			tmp_string = "40M";
		else
			tmp_string = "80M";
		PHYDM_SNPRINTF(output + used, out_len - used,
			       "\r\n %-35s %s %s", "mode", "VHT", tmp_string);
		rx_bw = rx_vht_bw;
	} else if (rx_ht == 1) {
		if (rx_ht_bw == 0)
			tmp_string = "20M";
		else if (rx_ht_bw == 1)
			tmp_string = "40M";
		PHYDM_SNPRINTF(output + used, out_len - used,
			       "\r\n %-35s %s %s", "mode", "HT", tmp_string);
		rx_bw = rx_ht_bw;
	} else {
		PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s %s",
			       "mode", "Legacy");
	}
	if (rx_ht != 0) {
		if (rxsc == 0)
			tmp_string = "duplicate/full bw";
		else if (rxsc == 1)
			tmp_string = "usc20-1";
		else if (rxsc == 2)
			tmp_string = "lsc20-1";
		else if (rxsc == 3)
			tmp_string = "usc20-2";
		else if (rxsc == 4)
			tmp_string = "lsc20-2";
		else if (rxsc == 9)
			tmp_string = "usc40";
		else if (rxsc == 10)
			tmp_string = "lsc40";
		PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s",
			       tmp_string);
	}

	/* RX signal power and AGC related info*/

	value32 = odm_get_bb_reg(dm, 0xF90, MASKDWORD);
	pwdb = (u8)((value32 & MASKBYTE1) >> 8);
	pwdb = pwdb >> 1;
	sig_power = -110 + pwdb;
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d",
		       "OFDM RX Signal Power(dB)", sig_power);

	value32 = odm_get_bb_reg(dm, 0xd14, MASKDWORD);
	rx_snr_path_a = (u8)(value32 & 0xFF) >> 1;
	rf_gain_path_a = (s8)((value32 & MASKBYTE1) >> 8);
	rf_gain_path_a *= 2;
	value32 = odm_get_bb_reg(dm, 0xd54, MASKDWORD);
	rx_snr_path_b = (u8)(value32 & 0xFF) >> 1;
	rf_gain_path_b = (s8)((value32 & MASKBYTE1) >> 8);
	rf_gain_path_b *= 2;
	value32 = odm_get_bb_reg(dm, 0xd94, MASKDWORD);
	rx_snr_path_c = (u8)(value32 & 0xFF) >> 1;
	rf_gain_path_c = (s8)((value32 & MASKBYTE1) >> 8);
	rf_gain_path_c *= 2;
	value32 = odm_get_bb_reg(dm, 0xdd4, MASKDWORD);
	rx_snr_path_d = (u8)(value32 & 0xFF) >> 1;
	rf_gain_path_d = (s8)((value32 & MASKBYTE1) >> 8);
	rf_gain_path_d *= 2;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d / %d",
		       "OFDM RX RF Gain(A/B/C/D)", rf_gain_path_a,
		       rf_gain_path_b, rf_gain_path_c, rf_gain_path_d);

	/* RX counter related info*/

	value32 = odm_get_bb_reg(dm, 0xF08, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d",
		       "OFDM CCA counter", ((value32 & 0xFFFF0000) >> 16));

	value32 = odm_get_bb_reg(dm, 0xFD0, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d",
		       "OFDM SBD Fail counter", value32 & 0xFFFF);

	value32 = odm_get_bb_reg(dm, 0xFC4, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "VHT SIGA/SIGB CRC8 Fail counter", value32 & 0xFFFF,
		       ((value32 & 0xFFFF0000) >> 16));

	value32 = odm_get_bb_reg(dm, 0xFCC, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d",
		       "CCK CCA counter", value32 & 0xFFFF);

	value32 = odm_get_bb_reg(dm, 0xFBC, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "LSIG (parity Fail/rate Illegal) counter",
		       value32 & 0xFFFF, ((value32 & 0xFFFF0000) >> 16));

	value32_1 = odm_get_bb_reg(dm, 0xFC8, MASKDWORD);
	value32_2 = odm_get_bb_reg(dm, 0xFC0, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "HT/VHT MCS NOT SUPPORT counter",
		       ((value32_2 & 0xFFFF0000) >> 16), value32_1 & 0xFFFF);

	/* PostFFT related info*/
	value32 = odm_get_bb_reg(dm, 0xF8c, MASKDWORD);
	rxevm_0 = (s8)((value32 & MASKBYTE2) >> 16);
	rxevm_0 /= 2;
	if (rxevm_0 < -63)
		rxevm_0 = 0;

	rxevm_1 = (s8)((value32 & MASKBYTE3) >> 24);
	rxevm_1 /= 2;
	value32 = odm_get_bb_reg(dm, 0xF88, MASKDWORD);
	rxevm_2 = (s8)((value32 & MASKBYTE2) >> 16);
	rxevm_2 /= 2;

	if (rxevm_1 < -63)
		rxevm_1 = 0;
	if (rxevm_2 < -63)
		rxevm_2 = 0;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d", "RXEVM (1ss/2ss/3ss)",
		       rxevm_0, rxevm_1, rxevm_2);
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d / %d", "RXSNR(A/B/C/D, dB)",
		       rx_snr_path_a, rx_snr_path_b, rx_snr_path_c,
		       rx_snr_path_d);

	value32 = odm_get_bb_reg(dm, 0xF8C, MASKDWORD);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "CSI_1st /CSI_2nd", value32 & 0xFFFF,
		       ((value32 & 0xFFFF0000) >> 16));

	/*BW & mode Detection*/

	/*Reset Page F counter*/
	odm_set_bb_reg(dm, 0xB58, BIT(0), 1);
	odm_set_bb_reg(dm, 0xB58, BIT(0), 0);

	/*CFO Report Info*/
	/*Short CFO*/
	value32 = odm_get_bb_reg(dm, 0xd0c, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xd4c, MASKDWORD);
	value32_2 = odm_get_bb_reg(dm, 0xd8c, MASKDWORD);
	value32_3 = odm_get_bb_reg(dm, 0xdcc, MASKDWORD);

	sfo_a = (s32)(value32 & 0xfff);
	sfo_b = (s32)(value32_1 & 0xfff);
	sfo_c = (s32)(value32_2 & 0xfff);
	sfo_d = (s32)(value32_3 & 0xfff);

	lfo_a = (s32)(value32 >> 16);
	lfo_b = (s32)(value32_1 >> 16);
	lfo_c = (s32)(value32_2 >> 16);
	lfo_d = (s32)(value32_3 >> 16);

	/*SFO 2's to dec*/
	if (sfo_a > 2047)
		sfo_a = sfo_a - 4096;
	sfo_a = (sfo_a * 312500) / 2048;
	if (sfo_b > 2047)
		sfo_b = sfo_b - 4096;
	sfo_b = (sfo_b * 312500) / 2048;
	if (sfo_c > 2047)
		sfo_c = sfo_c - 4096;
	sfo_c = (sfo_c * 312500) / 2048;
	if (sfo_d > 2047)
		sfo_d = sfo_d - 4096;
	sfo_d = (sfo_d * 312500) / 2048;

	/*LFO 2's to dec*/

	if (lfo_a > 4095)
		lfo_a = lfo_a - 8192;

	if (lfo_b > 4095)
		lfo_b = lfo_b - 8192;

	if (lfo_c > 4095)
		lfo_c = lfo_c - 8192;

	if (lfo_d > 4095)
		lfo_d = lfo_d - 8192;
	lfo_a = lfo_a * 312500 / 4096;
	lfo_b = lfo_b * 312500 / 4096;
	lfo_c = lfo_c * 312500 / 4096;
	lfo_d = lfo_d * 312500 / 4096;
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s",
		       "CFO Report Info");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d /%d",
		       "Short CFO(Hz) <A/B/C/D>", sfo_a, sfo_b, sfo_c, sfo_d);
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d /%d",
		       "Long CFO(Hz) <A/B/C/D>", lfo_a, lfo_b, lfo_c, lfo_d);

	/*SCFO*/
	value32 = odm_get_bb_reg(dm, 0xd10, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xd50, MASKDWORD);
	value32_2 = odm_get_bb_reg(dm, 0xd90, MASKDWORD);
	value32_3 = odm_get_bb_reg(dm, 0xdd0, MASKDWORD);

	sfo_a = (s32)(value32 & 0x7ff);
	sfo_b = (s32)(value32_1 & 0x7ff);
	sfo_c = (s32)(value32_2 & 0x7ff);
	sfo_d = (s32)(value32_3 & 0x7ff);

	if (sfo_a > 1023)
		sfo_a = sfo_a - 2048;

	if (sfo_b > 2047)
		sfo_b = sfo_b - 4096;

	if (sfo_c > 2047)
		sfo_c = sfo_c - 4096;

	if (sfo_d > 2047)
		sfo_d = sfo_d - 4096;

	sfo_a = sfo_a * 312500 / 1024;
	sfo_b = sfo_b * 312500 / 1024;
	sfo_c = sfo_c * 312500 / 1024;
	sfo_d = sfo_d * 312500 / 1024;

	lfo_a = (s32)(value32 >> 16);
	lfo_b = (s32)(value32_1 >> 16);
	lfo_c = (s32)(value32_2 >> 16);
	lfo_d = (s32)(value32_3 >> 16);

	if (lfo_a > 4095)
		lfo_a = lfo_a - 8192;

	if (lfo_b > 4095)
		lfo_b = lfo_b - 8192;

	if (lfo_c > 4095)
		lfo_c = lfo_c - 8192;

	if (lfo_d > 4095)
		lfo_d = lfo_d - 8192;
	lfo_a = lfo_a * 312500 / 4096;
	lfo_b = lfo_b * 312500 / 4096;
	lfo_c = lfo_c * 312500 / 4096;
	lfo_d = lfo_d * 312500 / 4096;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d /%d",
		       "value SCFO(Hz) <A/B/C/D>", sfo_a, sfo_b, sfo_c, sfo_d);
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d /%d", "ACQ CFO(Hz) <A/B/C/D>",
		       lfo_a, lfo_b, lfo_c, lfo_d);

	value32 = odm_get_bb_reg(dm, 0xd14, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xd54, MASKDWORD);
	value32_2 = odm_get_bb_reg(dm, 0xd94, MASKDWORD);
	value32_3 = odm_get_bb_reg(dm, 0xdd4, MASKDWORD);

	lfo_a = (s32)(value32 >> 16);
	lfo_b = (s32)(value32_1 >> 16);
	lfo_c = (s32)(value32_2 >> 16);
	lfo_d = (s32)(value32_3 >> 16);

	if (lfo_a > 4095)
		lfo_a = lfo_a - 8192;

	if (lfo_b > 4095)
		lfo_b = lfo_b - 8192;

	if (lfo_c > 4095)
		lfo_c = lfo_c - 8192;

	if (lfo_d > 4095)
		lfo_d = lfo_d - 8192;

	lfo_a = lfo_a * 312500 / 4096;
	lfo_b = lfo_b * 312500 / 4096;
	lfo_c = lfo_c * 312500 / 4096;
	lfo_d = lfo_d * 312500 / 4096;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d /%d", "End CFO(Hz) <A/B/C/D>",
		       lfo_a, lfo_b, lfo_c, lfo_d);

	value32 = odm_get_bb_reg(dm, 0xf20, MASKDWORD); /*L SIG*/

	tail = (u8)((value32 & 0xfc0000) >> 16);
	parity = (u8)((value32 & 0x20000) >> 16);
	length = (u16)((value32 & 0x1ffe00) >> 8);
	rsv = (u8)(value32 & 0x10);
	MCSS = (u8)(value32 & 0x0f);

	switch (MCSS) {
	case 0x0b:
		idx = 0;
		break;
	case 0x0f:
		idx = 1;
		break;
	case 0x0a:
		idx = 2;
		break;
	case 0x0e:
		idx = 3;
		break;
	case 0x09:
		idx = 4;
		break;
	case 0x08:
		idx = 5;
		break;
	case 0x0c:
		idx = 6;
		break;
	default:
		idx = 6;
		break;
	}

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s", "L-SIG");
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s : %s", "rate",
		       L_rate[idx]);
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x", "Rsv/length/parity", rsv,
		       rx_bw, length);

	value32 = odm_get_bb_reg(dm, 0xf2c, MASKDWORD); /*HT SIG*/
	if (rx_ht == 1) {
		hmcss = (u8)(value32 & 0x7F);
		hrx_bw = (u8)(value32 & 0x80);
		h_length = (u16)((value32 >> 8) & 0xffff);
	}
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s", "HT-SIG1");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x", "MCS/BW/length", hmcss,
		       hrx_bw, h_length);

	value32 = odm_get_bb_reg(dm, 0xf30, MASKDWORD); /*HT SIG*/

	if (rx_ht == 1) {
		smooth = (u8)(value32 & 0x01);
		htsound = (u8)(value32 & 0x02);
		rsv = (u8)(value32 & 0x04);
		agg = (u8)(value32 & 0x08);
		stbc = (u8)(value32 & 0x30);
		fec = (u8)(value32 & 0x40);
		sgi = (u8)(value32 & 0x80);
		htltf = (u8)((value32 & 0x300) >> 8);
		htcrc8 = (u16)((value32 & 0x3fc00) >> 8);
		tail = (u8)((value32 & 0xfc0000) >> 16);
	}
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s", "HT-SIG2");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x / %x / %x / %x",
		       "Smooth/NoSound/Rsv/Aggregate/STBC/LDPC", smooth,
		       htsound, rsv, agg, stbc, fec);
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x / %x",
		       "SGI/E-HT-LTFs/CRC/tail", sgi, htltf, htcrc8, tail);

	value32 = odm_get_bb_reg(dm, 0xf2c, MASKDWORD); /*VHT SIG A1*/
	if (rx_ht == 2) {
		/* value32 = odm_get_bb_reg(dm, 0xf2c,MASKDWORD);*/
		v_rx_bw = (u8)(value32 & 0x03);
		vrsv = (u8)(value32 & 0x04);
		vstbc = (u8)(value32 & 0x08);
		vgid = (u8)((value32 & 0x3f0) >> 4);
		v_nsts = (u8)(((value32 & 0x1c00) >> 8) + 1);
		vpaid = (u16)(value32 & 0x3fe);
		vtxops = (u8)((value32 & 0x400000) >> 20);
		vrsv2 = (u8)((value32 & 0x800000) >> 20);
	}
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s",
		       "VHT-SIG-A1");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x / %x / %x / %x / %x / %x",
		       "BW/Rsv1/STBC/GID/Nsts/PAID/TXOPPS/Rsv2", v_rx_bw, vrsv,
		       vstbc, vgid, v_nsts, vpaid, vtxops, vrsv2);

	value32 = odm_get_bb_reg(dm, 0xf30, MASKDWORD); /*VHT SIG*/

	if (rx_ht == 2) {
		/*value32 = odm_get_bb_reg(dm, 0xf30,MASKDWORD); */ /*VHT SIG*/

		/* sgi=(u8)(value32&0x01); */
		sgiext = (u8)(value32 & 0x03);
		/* fec = (u8)(value32&0x04); */
		fecext = (u8)(value32 & 0x0C);

		v_mcss = (u8)(value32 & 0xf0);
		bf = (u8)((value32 & 0x100) >> 8);
		vrsv = (u8)((value32 & 0x200) >> 8);
		vhtcrc8 = (u16)((value32 & 0x3fc00) >> 8);
		v_tail = (u8)((value32 & 0xfc0000) >> 16);
	}
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s",
		       "VHT-SIG-A2");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x / %x / %x / %x / %x",
		       "SGI/FEC/MCS/BF/Rsv/CRC/tail", sgiext, fecext, v_mcss,
		       bf, vrsv, vhtcrc8, v_tail);

	value32 = odm_get_bb_reg(dm, 0xf34, MASKDWORD); /*VHT SIG*/
	{
		v_length = (u16)(value32 & 0x1fffff);
		vbrsv = (u8)((value32 & 0x600000) >> 20);
		vb_tail = (u16)((value32 & 0x1f800000) >> 20);
		vbcrc = (u8)((value32 & 0x80000000) >> 28);
	}
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s",
		       "VHT-SIG-B");
	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %x / %x / %x / %x", "length/Rsv/tail/CRC",
		       v_length, vbrsv, vb_tail, vbcrc);

	/*for Condition number*/
	if (dm->support_ic_type & ODM_RTL8822B) {
		s32 condition_num = 0;
		char *factor = NULL;

		/*enable report condition number*/
		odm_set_bb_reg(dm, 0x1988, BIT(22), 0x1);

		condition_num = odm_get_bb_reg(dm, 0xf84, MASKDWORD);
		condition_num = (condition_num & 0x3ffff) >> 4;

		if (*dm->band_width == ODM_BW80M) {
			factor = "256/234";
		} else if (*dm->band_width == ODM_BW40M) {
			factor = "128/108";
		} else if (*dm->band_width == ODM_BW20M) {
			if (rx_ht == 2 || rx_ht == 1)
				factor = "64/52"; /*HT or VHT*/
			else
				factor = "64/48"; /*legacy*/
		}

		PHYDM_SNPRINTF(output + used, out_len - used,
			       "\r\n %-35s = %d (factor = %s)",
			       "Condition number", condition_num, factor);
	}
}