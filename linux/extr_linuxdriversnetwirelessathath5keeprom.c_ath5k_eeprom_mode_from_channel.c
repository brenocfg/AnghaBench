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
struct ieee80211_channel {int hw_value; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int AR5K_EEPROM_MODE_11A ; 
 int AR5K_EEPROM_MODE_11B ; 
 int AR5K_EEPROM_MODE_11G ; 
#define  AR5K_MODE_11A 130 
#define  AR5K_MODE_11B 129 
#define  AR5K_MODE_11G 128 
 int /*<<< orphan*/  ATH5K_WARN (struct ath5k_hw*,char*) ; 

int
ath5k_eeprom_mode_from_channel(struct ath5k_hw *ah,
		struct ieee80211_channel *channel)
{
	switch (channel->hw_value) {
	case AR5K_MODE_11A:
		return AR5K_EEPROM_MODE_11A;
	case AR5K_MODE_11G:
		return AR5K_EEPROM_MODE_11G;
	case AR5K_MODE_11B:
		return AR5K_EEPROM_MODE_11B;
	default:
		ATH5K_WARN(ah, "channel is not A/B/G!");
		return AR5K_EEPROM_MODE_11A;
	}
}