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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_channel {scalar_t__ band; int center_freq; } ;
struct ath5k_eeprom_info {int** ee_spur_chans; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {int ah_bwmode; TYPE_1__ ah_capabilities; } ;
typedef  int s32 ;

/* Variables and functions */
#define  AR5K_BWMODE_10MHZ 130 
#define  AR5K_BWMODE_40MHZ 129 
#define  AR5K_BWMODE_5MHZ 128 
 size_t AR5K_EEPROM_BAND_2GHZ ; 
 size_t AR5K_EEPROM_BAND_5GHZ ; 
 int AR5K_EEPROM_NO_SPUR ; 
 size_t AR5K_EEPROM_N_SPUR_CHANS ; 
 int AR5K_EEPROM_SPUR_CHAN_MASK ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK2_1 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK2_2 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK2_3 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK2_4 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK2_4_MASK_4 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_1 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_2 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_3 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_CTL ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_CTL_MASK_4 ; 
 int /*<<< orphan*/  AR5K_PHY_BIN_MASK_CTL_RATE ; 
 int /*<<< orphan*/  AR5K_PHY_IQ ; 
 int AR5K_PHY_IQ_CHAN_MASK_EN ; 
 int AR5K_PHY_IQ_PILOT_MASK_EN ; 
 int AR5K_PHY_IQ_SPUR_FILT_EN ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_10 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_10_PILOT_MASK_2 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_11 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_11_SPUR_FREQ_SD ; 
 int AR5K_PHY_TIMING_11_USE_SPUR_IN_AGC ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_7 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_8 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_8_PILOT_MASK_2 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_9 ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int AR5K_REG_SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int AR5K_SPUR_CHAN_WIDTH ; 
 int AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_hw_set_spur_mitigation_filter(struct ath5k_hw *ah,
				struct ieee80211_channel *channel)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 mag_mask[4] = {0, 0, 0, 0};
	u32 pilot_mask[2] = {0, 0};
	/* Note: fbin values are scaled up by 2 */
	u16 spur_chan_fbin, chan_fbin, symbol_width, spur_detection_window;
	s32 spur_delta_phase, spur_freq_sigma_delta;
	s32 spur_offset, num_symbols_x16;
	u8 num_symbol_offsets, i, freq_band;

	/* Convert current frequency to fbin value (the same way channels
	 * are stored on EEPROM, check out ath5k_eeprom_bin2freq) and scale
	 * up by 2 so we can compare it later */
	if (channel->band == NL80211_BAND_2GHZ) {
		chan_fbin = (channel->center_freq - 2300) * 10;
		freq_band = AR5K_EEPROM_BAND_2GHZ;
	} else {
		chan_fbin = (channel->center_freq - 4900) * 10;
		freq_band = AR5K_EEPROM_BAND_5GHZ;
	}

	/* Check if any spur_chan_fbin from EEPROM is
	 * within our current channel's spur detection range */
	spur_chan_fbin = AR5K_EEPROM_NO_SPUR;
	spur_detection_window = AR5K_SPUR_CHAN_WIDTH;
	/* XXX: Half/Quarter channels ?*/
	if (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
		spur_detection_window *= 2;

	for (i = 0; i < AR5K_EEPROM_N_SPUR_CHANS; i++) {
		spur_chan_fbin = ee->ee_spur_chans[i][freq_band];

		/* Note: mask cleans AR5K_EEPROM_NO_SPUR flag
		 * so it's zero if we got nothing from EEPROM */
		if (spur_chan_fbin == AR5K_EEPROM_NO_SPUR) {
			spur_chan_fbin &= AR5K_EEPROM_SPUR_CHAN_MASK;
			break;
		}

		if ((chan_fbin - spur_detection_window <=
		(spur_chan_fbin & AR5K_EEPROM_SPUR_CHAN_MASK)) &&
		(chan_fbin + spur_detection_window >=
		(spur_chan_fbin & AR5K_EEPROM_SPUR_CHAN_MASK))) {
			spur_chan_fbin &= AR5K_EEPROM_SPUR_CHAN_MASK;
			break;
		}
	}

	/* We need to enable spur filter for this channel */
	if (spur_chan_fbin) {
		spur_offset = spur_chan_fbin - chan_fbin;
		/*
		 * Calculate deltas:
		 * spur_freq_sigma_delta -> spur_offset / sample_freq << 21
		 * spur_delta_phase -> spur_offset / chip_freq << 11
		 * Note: Both values have 100Hz resolution
		 */
		switch (ah->ah_bwmode) {
		case AR5K_BWMODE_40MHZ:
			/* Both sample_freq and chip_freq are 80MHz */
			spur_delta_phase = (spur_offset << 16) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz * 2;
			break;
		case AR5K_BWMODE_10MHZ:
			/* Both sample_freq and chip_freq are 20MHz (?) */
			spur_delta_phase = (spur_offset << 18) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz / 2;
			break;
		case AR5K_BWMODE_5MHZ:
			/* Both sample_freq and chip_freq are 10MHz (?) */
			spur_delta_phase = (spur_offset << 19) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz / 4;
			break;
		default:
			if (channel->band == NL80211_BAND_5GHZ) {
				/* Both sample_freq and chip_freq are 40MHz */
				spur_delta_phase = (spur_offset << 17) / 25;
				spur_freq_sigma_delta =
						(spur_delta_phase >> 10);
				symbol_width =
					AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz;
			} else {
				/* sample_freq -> 40MHz chip_freq -> 44MHz
				 * (for b compatibility) */
				spur_delta_phase = (spur_offset << 17) / 25;
				spur_freq_sigma_delta =
						(spur_offset << 8) / 55;
				symbol_width =
					AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz;
			}
			break;
		}

		/* Calculate pilot and magnitude masks */

		/* Scale up spur_offset by 1000 to switch to 100HZ resolution
		 * and divide by symbol_width to find how many symbols we have
		 * Note: number of symbols is scaled up by 16 */
		num_symbols_x16 = ((spur_offset * 1000) << 4) / symbol_width;

		/* Spur is on a symbol if num_symbols_x16 % 16 is zero */
		if (!(num_symbols_x16 & 0xF))
			/* _X_ */
			num_symbol_offsets = 3;
		else
			/* _xx_ */
			num_symbol_offsets = 4;

		for (i = 0; i < num_symbol_offsets; i++) {

			/* Calculate pilot mask */
			s32 curr_sym_off =
				(num_symbols_x16 / 16) + i + 25;

			/* Pilot magnitude mask seems to be a way to
			 * declare the boundaries for our detection
			 * window or something, it's 2 for the middle
			 * value(s) where the symbol is expected to be
			 * and 1 on the boundary values */
			u8 plt_mag_map =
				(i == 0 || i == (num_symbol_offsets - 1))
								? 1 : 2;

			if (curr_sym_off >= 0 && curr_sym_off <= 32) {
				if (curr_sym_off <= 25)
					pilot_mask[0] |= 1 << curr_sym_off;
				else if (curr_sym_off >= 27)
					pilot_mask[0] |= 1 << (curr_sym_off - 1);
			} else if (curr_sym_off >= 33 && curr_sym_off <= 52)
				pilot_mask[1] |= 1 << (curr_sym_off - 33);

			/* Calculate magnitude mask (for viterbi decoder) */
			if (curr_sym_off >= -1 && curr_sym_off <= 14)
				mag_mask[0] |=
					plt_mag_map << (curr_sym_off + 1) * 2;
			else if (curr_sym_off >= 15 && curr_sym_off <= 30)
				mag_mask[1] |=
					plt_mag_map << (curr_sym_off - 15) * 2;
			else if (curr_sym_off >= 31 && curr_sym_off <= 46)
				mag_mask[2] |=
					plt_mag_map << (curr_sym_off - 31) * 2;
			else if (curr_sym_off >= 47 && curr_sym_off <= 53)
				mag_mask[3] |=
					plt_mag_map << (curr_sym_off - 47) * 2;

		}

		/* Write settings on hw to enable spur filter */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_RATE, 0xff);
		/* XXX: Self correlator also ? */
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ,
					AR5K_PHY_IQ_PILOT_MASK_EN |
					AR5K_PHY_IQ_CHAN_MASK_EN |
					AR5K_PHY_IQ_SPUR_FILT_EN);

		/* Set delta phase and freq sigma delta */
		ath5k_hw_reg_write(ah,
				AR5K_REG_SM(spur_delta_phase,
					AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE) |
				AR5K_REG_SM(spur_freq_sigma_delta,
				AR5K_PHY_TIMING_11_SPUR_FREQ_SD) |
				AR5K_PHY_TIMING_11_USE_SPUR_IN_AGC,
				AR5K_PHY_TIMING_11);

		/* Write pilot masks */
		ath5k_hw_reg_write(ah, pilot_mask[0], AR5K_PHY_TIMING_7);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_8,
					AR5K_PHY_TIMING_8_PILOT_MASK_2,
					pilot_mask[1]);

		ath5k_hw_reg_write(ah, pilot_mask[0], AR5K_PHY_TIMING_9);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_10,
					AR5K_PHY_TIMING_10_PILOT_MASK_2,
					pilot_mask[1]);

		/* Write magnitude masks */
		ath5k_hw_reg_write(ah, mag_mask[0], AR5K_PHY_BIN_MASK_1);
		ath5k_hw_reg_write(ah, mag_mask[1], AR5K_PHY_BIN_MASK_2);
		ath5k_hw_reg_write(ah, mag_mask[2], AR5K_PHY_BIN_MASK_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_MASK_4,
					mag_mask[3]);

		ath5k_hw_reg_write(ah, mag_mask[0], AR5K_PHY_BIN_MASK2_1);
		ath5k_hw_reg_write(ah, mag_mask[1], AR5K_PHY_BIN_MASK2_2);
		ath5k_hw_reg_write(ah, mag_mask[2], AR5K_PHY_BIN_MASK2_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK2_4,
					AR5K_PHY_BIN_MASK2_4_MASK_4,
					mag_mask[3]);

	} else if (ath5k_hw_reg_read(ah, AR5K_PHY_IQ) &
	AR5K_PHY_IQ_SPUR_FILT_EN) {
		/* Clean up spur mitigation settings and disable filter */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_RATE, 0);
		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_IQ,
					AR5K_PHY_IQ_PILOT_MASK_EN |
					AR5K_PHY_IQ_CHAN_MASK_EN |
					AR5K_PHY_IQ_SPUR_FILT_EN);
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_TIMING_11);

		/* Clear pilot masks */
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_TIMING_7);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_8,
					AR5K_PHY_TIMING_8_PILOT_MASK_2,
					0);

		ath5k_hw_reg_write(ah, 0, AR5K_PHY_TIMING_9);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_10,
					AR5K_PHY_TIMING_10_PILOT_MASK_2,
					0);

		/* Clear magnitude masks */
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK_1);
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK_2);
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_MASK_4,
					0);

		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK2_1);
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK2_2);
		ath5k_hw_reg_write(ah, 0, AR5K_PHY_BIN_MASK2_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK2_4,
					AR5K_PHY_BIN_MASK2_4_MASK_4,
					0);
	}
}