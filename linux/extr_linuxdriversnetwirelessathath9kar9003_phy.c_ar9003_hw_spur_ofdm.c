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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK ; 
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int /*<<< orphan*/  AR_PHY_MODE_DYNAMIC ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_ENABLE_MASK_PPM ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_MASK_RATE_CNTL ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_SPUR_RSSI_THRESH ; 
 int /*<<< orphan*/  AR_PHY_TIMING11 ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_SPUR_DELTA_PHASE ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_SPUR_FREQ_SD ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR ; 
 int /*<<< orphan*/  AR_PHY_TIMING4 ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_CHAN_MASK ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_PILOT_MASK ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_SPUR_FILTER ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_SPUR_RSSI ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_hw_spur_ofdm(struct ath_hw *ah,
				int freq_offset,
				int spur_freq_sd,
				int spur_delta_phase,
				int spur_subchannel_sd,
				int range,
				int synth_freq)
{
	int mask_index = 0;

	/* OFDM Spur mitigation */
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		 AR_PHY_TIMING4_ENABLE_SPUR_FILTER, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_FREQ_SD, spur_freq_sd);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_DELTA_PHASE, spur_delta_phase);
	REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
		      AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD, spur_subchannel_sd);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC, 0x1);

	if (!(AR_SREV_9565(ah) && range == 10 && synth_freq == 2437))
		REG_RMW_FIELD(ah, AR_PHY_TIMING11,
			      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR, 0x1);

	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_SPUR_RSSI, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_SPUR_RSSI_THRESH, 34);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI, 1);

	if (!AR_SREV_9340(ah) &&
	    REG_READ_FIELD(ah, AR_PHY_MODE,
			   AR_PHY_MODE_DYNAMIC) == 0x1)
		REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
			      AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT, 1);

	mask_index = (freq_offset << 4) / 5;
	if (mask_index < 0)
		mask_index = mask_index - 1;

	mask_index = mask_index & 0x7f;

	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_ENABLE_MASK_PPM, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_PILOT_MASK, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_CHAN_MASK, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A, 0xc);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A, 0xc);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0xa0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_MASK_RATE_CNTL, 0xff);
}