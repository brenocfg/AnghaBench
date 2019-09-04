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
struct cfg80211_chan_def {int width; TYPE_2__* chan; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_bwmode; TYPE_1__* curchan; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_BWMODE_10MHZ ; 
 int /*<<< orphan*/  AR5K_BWMODE_5MHZ ; 
 int /*<<< orphan*/  AR5K_BWMODE_DEFAULT ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int EINVAL ; 
#define  NL80211_CHAN_WIDTH_10 131 
#define  NL80211_CHAN_WIDTH_20 130 
#define  NL80211_CHAN_WIDTH_20_NOHT 129 
#define  NL80211_CHAN_WIDTH_5 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ath5k_reset (struct ath5k_hw*,TYPE_2__*,int) ; 

int
ath5k_chan_set(struct ath5k_hw *ah, struct cfg80211_chan_def *chandef)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
		  "channel set, resetting (%u -> %u MHz)\n",
		  ah->curchan->center_freq, chandef->chan->center_freq);

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_20:
	case NL80211_CHAN_WIDTH_20_NOHT:
		ah->ah_bwmode = AR5K_BWMODE_DEFAULT;
		break;
	case NL80211_CHAN_WIDTH_5:
		ah->ah_bwmode = AR5K_BWMODE_5MHZ;
		break;
	case NL80211_CHAN_WIDTH_10:
		ah->ah_bwmode = AR5K_BWMODE_10MHZ;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	/*
	 * To switch channels clear any pending DMA operations;
	 * wait long enough for the RX fifo to drain, reset the
	 * hardware at the new frequency, and then re-enable
	 * the relevant bits of the h/w.
	 */
	return ath5k_reset(ah, chandef->chan, true);
}