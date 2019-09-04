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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_PHY_AIC_SRAM_ADDR_B0 ; 
 scalar_t__ AR_PHY_AIC_SRAM_DATA_B0 ; 
 scalar_t__ AR_PHY_BT_COEX_4 ; 
 scalar_t__ AR_PHY_BT_COEX_5 ; 
 int ATH_AIC_SRAM_AUTO_INCREMENT ; 
 int ATH_AIC_SRAM_GAIN_TABLE_OFFSET ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 

__attribute__((used)) static void ar9003_aic_gain_table(struct ath_hw *ah)
{
	u32 aic_atten_word[19], i;

	/* Config LNA gain difference */
	REG_WRITE(ah, AR_PHY_BT_COEX_4, 0x2c200a00);
	REG_WRITE(ah, AR_PHY_BT_COEX_5, 0x5c4e4438);

	/* Program gain table */
	aic_atten_word[0] = (0x1 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x0 & 0xf) << 5 |
		(0x1f & 0x1f); /* -01 dB: 4'd1, 5'd31,  00 dB: 4'd0, 5'd31 */
	aic_atten_word[1] = (0x3 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x2 & 0xf) << 5 |
		(0x1f & 0x1f); /* -03 dB: 4'd3, 5'd31, -02 dB: 4'd2, 5'd31 */
	aic_atten_word[2] = (0x5 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x4 & 0xf) << 5 |
		(0x1f & 0x1f); /* -05 dB: 4'd5, 5'd31, -04 dB: 4'd4, 5'd31 */
	aic_atten_word[3] = (0x1 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x0 & 0xf) << 5 |
		(0x1e & 0x1f); /* -07 dB: 4'd1, 5'd30, -06 dB: 4'd0, 5'd30 */
	aic_atten_word[4] = (0x3 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x2 & 0xf) << 5 |
		(0x1e & 0x1f); /* -09 dB: 4'd3, 5'd30, -08 dB: 4'd2, 5'd30 */
	aic_atten_word[5] = (0x5 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x4 & 0xf) << 5 |
		(0x1e & 0x1f); /* -11 dB: 4'd5, 5'd30, -10 dB: 4'd4, 5'd30 */
	aic_atten_word[6] = (0x1 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0xf & 0x1f);  /* -13 dB: 4'd1, 5'd15, -12 dB: 4'd0, 5'd15 */
	aic_atten_word[7] = (0x3 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0xf & 0x1f);  /* -15 dB: 4'd3, 5'd15, -14 dB: 4'd2, 5'd15 */
	aic_atten_word[8] = (0x5 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0xf & 0x1f);  /* -17 dB: 4'd5, 5'd15, -16 dB: 4'd4, 5'd15 */
	aic_atten_word[9] = (0x1 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -19 dB: 4'd1, 5'd07, -18 dB: 4'd0, 5'd07 */
	aic_atten_word[10] = (0x3 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -21 dB: 4'd3, 5'd07, -20 dB: 4'd2, 5'd07 */
	aic_atten_word[11] = (0x5 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -23 dB: 4'd5, 5'd07, -22 dB: 4'd4, 5'd07 */
	aic_atten_word[12] = (0x7 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x6 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -25 dB: 4'd7, 5'd07, -24 dB: 4'd6, 5'd07 */
	aic_atten_word[13] = (0x3 & 0xf) << 14 | (0x3 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x3 & 0x1f);  /* -27 dB: 4'd3, 5'd03, -26 dB: 4'd2, 5'd03 */
	aic_atten_word[14] = (0x5 & 0xf) << 14 | (0x3 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x3 & 0x1f);  /* -29 dB: 4'd5, 5'd03, -28 dB: 4'd4, 5'd03 */
	aic_atten_word[15] = (0x1 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -31 dB: 4'd1, 5'd01, -30 dB: 4'd0, 5'd01 */
	aic_atten_word[16] = (0x3 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -33 dB: 4'd3, 5'd01, -32 dB: 4'd2, 5'd01 */
	aic_atten_word[17] = (0x5 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -35 dB: 4'd5, 5'd01, -34 dB: 4'd4, 5'd01 */
	aic_atten_word[18] = (0x7 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x6 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -37 dB: 4'd7, 5'd01, -36 dB: 4'd6, 5'd01 */

	/* Write to Gain table with auto increment enabled. */
	REG_WRITE(ah, (AR_PHY_AIC_SRAM_ADDR_B0 + 0x3000),
		  (ATH_AIC_SRAM_AUTO_INCREMENT |
		   ATH_AIC_SRAM_GAIN_TABLE_OFFSET));

	for (i = 0; i < 19; i++) {
		REG_WRITE(ah, (AR_PHY_AIC_SRAM_DATA_B0 + 0x3000),
			  aic_atten_word[i]);
	}
}