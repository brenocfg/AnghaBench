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
struct ieee80211_rate {int bitrate; } ;
struct ath5k_hw {int ah_bwmode; int /*<<< orphan*/  hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  AR5K_BWMODE_10MHZ 130 
#define  AR5K_BWMODE_40MHZ 129 
#define  AR5K_BWMODE_5MHZ 128 
 int AR5K_INIT_OFDM_PLCP_BITS ; 
 int AR5K_INIT_OFDM_PREAMBLE_TIME_MIN ; 
 int AR5K_INIT_OFDM_PREAMPLE_TIME ; 
 int AR5K_INIT_OFDM_SYMBOL_TIME ; 
 int AR5K_INIT_SIFS_DEFAULT_BG ; 
 int AR5K_INIT_SIFS_HALF_RATE ; 
 int AR5K_INIT_SIFS_QUARTER_RATE ; 
 int AR5K_INIT_SIFS_TURBO ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ieee80211_generic_frame_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct ieee80211_rate*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

int
ath5k_hw_get_frame_duration(struct ath5k_hw *ah, enum nl80211_band band,
		int len, struct ieee80211_rate *rate, bool shortpre)
{
	int sifs, preamble, plcp_bits, sym_time;
	int bitrate, bits, symbols, symbol_bits;
	int dur;

	/* Fallback */
	if (!ah->ah_bwmode) {
		__le16 raw_dur = ieee80211_generic_frame_duration(ah->hw,
					NULL, band, len, rate);

		/* subtract difference between long and short preamble */
		dur = le16_to_cpu(raw_dur);
		if (shortpre)
			dur -= 96;

		return dur;
	}

	bitrate = rate->bitrate;
	preamble = AR5K_INIT_OFDM_PREAMPLE_TIME;
	plcp_bits = AR5K_INIT_OFDM_PLCP_BITS;
	sym_time = AR5K_INIT_OFDM_SYMBOL_TIME;

	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		sifs = AR5K_INIT_SIFS_TURBO;
		preamble = AR5K_INIT_OFDM_PREAMBLE_TIME_MIN;
		break;
	case AR5K_BWMODE_10MHZ:
		sifs = AR5K_INIT_SIFS_HALF_RATE;
		preamble *= 2;
		sym_time *= 2;
		bitrate = DIV_ROUND_UP(bitrate, 2);
		break;
	case AR5K_BWMODE_5MHZ:
		sifs = AR5K_INIT_SIFS_QUARTER_RATE;
		preamble *= 4;
		sym_time *= 4;
		bitrate = DIV_ROUND_UP(bitrate, 4);
		break;
	default:
		sifs = AR5K_INIT_SIFS_DEFAULT_BG;
		break;
	}

	bits = plcp_bits + (len << 3);
	/* Bit rate is in 100Kbits */
	symbol_bits = bitrate * sym_time;
	symbols = DIV_ROUND_UP(bits * 10, symbol_bits);

	dur = sifs + preamble + (sym_time * symbols);

	return dur;
}