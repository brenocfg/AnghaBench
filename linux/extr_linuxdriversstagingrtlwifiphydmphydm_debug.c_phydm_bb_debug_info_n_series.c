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
struct phy_dm_struct {int dummy; } ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int MASKBYTE2 ; 
 int MASKBYTE3 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,...) ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phydm_bb_debug_info_n_series(void *dm_void, u32 *_used,
					 char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;

	u32 value32 = 0, value32_1 = 0;
	u8 rf_gain_a = 0, rf_gain_b = 0, rf_gain_c = 0, rf_gain_d = 0;
	u8 rx_snr_a = 0, rx_snr_b = 0, rx_snr_c = 0, rx_snr_d = 0;

	s8 rxevm_0 = 0, rxevm_1 = 0;
	s32 short_cfo_a = 0, short_cfo_b = 0, long_cfo_a = 0, long_cfo_b = 0;
	s32 scfo_a = 0, scfo_b = 0, avg_cfo_a = 0, avg_cfo_b = 0;
	s32 cfo_end_a = 0, cfo_end_b = 0, acq_cfo_a = 0, acq_cfo_b = 0;

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s\n",
		       "BB Report Info");

	/*AGC result*/
	value32 = odm_get_bb_reg(dm, 0xdd0, MASKDWORD);
	rf_gain_a = (u8)(value32 & 0x3f);
	rf_gain_a = rf_gain_a << 1;

	rf_gain_b = (u8)((value32 >> 8) & 0x3f);
	rf_gain_b = rf_gain_b << 1;

	rf_gain_c = (u8)((value32 >> 16) & 0x3f);
	rf_gain_c = rf_gain_c << 1;

	rf_gain_d = (u8)((value32 >> 24) & 0x3f);
	rf_gain_d = rf_gain_d << 1;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d / %d",
		       "OFDM RX RF Gain(A/B/C/D)", rf_gain_a, rf_gain_b,
		       rf_gain_c, rf_gain_d);

	/*SNR report*/
	value32 = odm_get_bb_reg(dm, 0xdd4, MASKDWORD);
	rx_snr_a = (u8)(value32 & 0xff);
	rx_snr_a = rx_snr_a >> 1;

	rx_snr_b = (u8)((value32 >> 8) & 0xff);
	rx_snr_b = rx_snr_b >> 1;

	rx_snr_c = (u8)((value32 >> 16) & 0xff);
	rx_snr_c = rx_snr_c >> 1;

	rx_snr_d = (u8)((value32 >> 24) & 0xff);
	rx_snr_d = rx_snr_d >> 1;

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "\r\n %-35s = %d / %d / %d / %d", "RXSNR(A/B/C/D, dB)",
		       rx_snr_a, rx_snr_b, rx_snr_c, rx_snr_d);

	/* PostFFT related info*/
	value32 = odm_get_bb_reg(dm, 0xdd8, MASKDWORD);

	rxevm_0 = (s8)((value32 & MASKBYTE2) >> 16);
	rxevm_0 /= 2;
	if (rxevm_0 < -63)
		rxevm_0 = 0;

	rxevm_1 = (s8)((value32 & MASKBYTE3) >> 24);
	rxevm_1 /= 2;
	if (rxevm_1 < -63)
		rxevm_1 = 0;

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "RXEVM (1ss/2ss)", rxevm_0, rxevm_1);

	/*CFO Report Info*/
	odm_set_bb_reg(dm, 0xd00, BIT(26), 1);

	/*Short CFO*/
	value32 = odm_get_bb_reg(dm, 0xdac, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xdb0, MASKDWORD);

	short_cfo_b = (s32)(value32 & 0xfff); /*S(12,11)*/
	short_cfo_a = (s32)((value32 & 0x0fff0000) >> 16);

	long_cfo_b = (s32)(value32_1 & 0x1fff); /*S(13,12)*/
	long_cfo_a = (s32)((value32_1 & 0x1fff0000) >> 16);

	/*SFO 2's to dec*/
	if (short_cfo_a > 2047)
		short_cfo_a = short_cfo_a - 4096;
	if (short_cfo_b > 2047)
		short_cfo_b = short_cfo_b - 4096;

	short_cfo_a = (short_cfo_a * 312500) / 2048;
	short_cfo_b = (short_cfo_b * 312500) / 2048;

	/*LFO 2's to dec*/

	if (long_cfo_a > 4095)
		long_cfo_a = long_cfo_a - 8192;

	if (long_cfo_b > 4095)
		long_cfo_b = long_cfo_b - 8192;

	long_cfo_a = long_cfo_a * 312500 / 4096;
	long_cfo_b = long_cfo_b * 312500 / 4096;

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s",
		       "CFO Report Info");
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "Short CFO(Hz) <A/B>", short_cfo_a, short_cfo_b);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "Long CFO(Hz) <A/B>", long_cfo_a, long_cfo_b);

	/*SCFO*/
	value32 = odm_get_bb_reg(dm, 0xdb8, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xdb4, MASKDWORD);

	scfo_b = (s32)(value32 & 0x7ff); /*S(11,10)*/
	scfo_a = (s32)((value32 & 0x07ff0000) >> 16);

	if (scfo_a > 1023)
		scfo_a = scfo_a - 2048;

	if (scfo_b > 1023)
		scfo_b = scfo_b - 2048;

	scfo_a = scfo_a * 312500 / 1024;
	scfo_b = scfo_b * 312500 / 1024;

	avg_cfo_b = (s32)(value32_1 & 0x1fff); /*S(13,12)*/
	avg_cfo_a = (s32)((value32_1 & 0x1fff0000) >> 16);

	if (avg_cfo_a > 4095)
		avg_cfo_a = avg_cfo_a - 8192;

	if (avg_cfo_b > 4095)
		avg_cfo_b = avg_cfo_b - 8192;

	avg_cfo_a = avg_cfo_a * 312500 / 4096;
	avg_cfo_b = avg_cfo_b * 312500 / 4096;

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "value SCFO(Hz) <A/B>", scfo_a, scfo_b);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "Avg CFO(Hz) <A/B>", avg_cfo_a, avg_cfo_b);

	value32 = odm_get_bb_reg(dm, 0xdbc, MASKDWORD);
	value32_1 = odm_get_bb_reg(dm, 0xde0, MASKDWORD);

	cfo_end_b = (s32)(value32 & 0x1fff); /*S(13,12)*/
	cfo_end_a = (s32)((value32 & 0x1fff0000) >> 16);

	if (cfo_end_a > 4095)
		cfo_end_a = cfo_end_a - 8192;

	if (cfo_end_b > 4095)
		cfo_end_b = cfo_end_b - 8192;

	cfo_end_a = cfo_end_a * 312500 / 4096;
	cfo_end_b = cfo_end_b * 312500 / 4096;

	acq_cfo_b = (s32)(value32_1 & 0x1fff); /*S(13,12)*/
	acq_cfo_a = (s32)((value32_1 & 0x1fff0000) >> 16);

	if (acq_cfo_a > 4095)
		acq_cfo_a = acq_cfo_a - 8192;

	if (acq_cfo_b > 4095)
		acq_cfo_b = acq_cfo_b - 8192;

	acq_cfo_a = acq_cfo_a * 312500 / 4096;
	acq_cfo_b = acq_cfo_b * 312500 / 4096;

	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "End CFO(Hz) <A/B>", cfo_end_a, cfo_end_b);
	PHYDM_SNPRINTF(output + used, out_len - used, "\r\n %-35s = %d / %d",
		       "ACQ CFO(Hz) <A/B>", acq_cfo_a, acq_cfo_b);
}