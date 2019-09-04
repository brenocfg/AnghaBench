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
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;
struct ath5k_hw {int ah_bwmode; int /*<<< orphan*/  ah_short_slot; struct ieee80211_channel* ah_current_channel; } ;

/* Variables and functions */
#define  AR5K_BWMODE_10MHZ 131 
#define  AR5K_BWMODE_40MHZ 130 
#define  AR5K_BWMODE_5MHZ 129 
#define  AR5K_BWMODE_DEFAULT 128 
 unsigned int AR5K_INIT_SLOT_TIME_B ; 
 unsigned int AR5K_INIT_SLOT_TIME_DEFAULT ; 
 unsigned int AR5K_INIT_SLOT_TIME_HALF_RATE ; 
 unsigned int AR5K_INIT_SLOT_TIME_QUARTER_RATE ; 
 unsigned int AR5K_INIT_SLOT_TIME_TURBO ; 
 int /*<<< orphan*/  AR5K_MODE_11B ; 

unsigned int
ath5k_hw_get_default_slottime(struct ath5k_hw *ah)
{
	struct ieee80211_channel *channel = ah->ah_current_channel;
	unsigned int slot_time;

	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_TURBO;
		break;
	case AR5K_BWMODE_10MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_HALF_RATE;
		break;
	case AR5K_BWMODE_5MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_QUARTER_RATE;
		break;
	case AR5K_BWMODE_DEFAULT:
	default:
		slot_time = AR5K_INIT_SLOT_TIME_DEFAULT;
		if ((channel->hw_value == AR5K_MODE_11B) && !ah->ah_short_slot)
			slot_time = AR5K_INIT_SLOT_TIME_B;
		break;
	}

	return slot_time;
}