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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct iwl_cfg {scalar_t__ nvm_type; } ;

/* Variables and functions */
 scalar_t__ FIRST_2GHZ_HT_MINUS ; 
 scalar_t__ IEEE80211_CHAN_INDOOR_ONLY ; 
 scalar_t__ IEEE80211_CHAN_IR_CONCURRENT ; 
 scalar_t__ IEEE80211_CHAN_NO_160MHZ ; 
 scalar_t__ IEEE80211_CHAN_NO_80MHZ ; 
 scalar_t__ IEEE80211_CHAN_NO_HT40 ; 
 scalar_t__ IEEE80211_CHAN_NO_HT40MINUS ; 
 scalar_t__ IEEE80211_CHAN_NO_HT40PLUS ; 
 scalar_t__ IEEE80211_CHAN_NO_IR ; 
 scalar_t__ IEEE80211_CHAN_RADAR ; 
 scalar_t__ IWL_NVM_EXT ; 
 scalar_t__ LAST_2GHZ_HT_PLUS ; 
 scalar_t__ LAST_5GHZ_HT ; 
 scalar_t__ LAST_5GHZ_HT_FAMILY_8000 ; 
 int NUM_2GHZ_CHANNELS ; 
 int NVM_CHANNEL_160MHZ ; 
 int NVM_CHANNEL_40MHZ ; 
 int NVM_CHANNEL_80MHZ ; 
 int NVM_CHANNEL_ACTIVE ; 
 int NVM_CHANNEL_GO_CONCURRENT ; 
 int NVM_CHANNEL_IBSS ; 
 int NVM_CHANNEL_INDOOR_ONLY ; 
 int NVM_CHANNEL_RADAR ; 

__attribute__((used)) static u32 iwl_get_channel_flags(u8 ch_num, int ch_idx, bool is_5ghz,
				 u16 nvm_flags, const struct iwl_cfg *cfg)
{
	u32 flags = IEEE80211_CHAN_NO_HT40;
	u32 last_5ghz_ht = LAST_5GHZ_HT;

	if (cfg->nvm_type == IWL_NVM_EXT)
		last_5ghz_ht = LAST_5GHZ_HT_FAMILY_8000;

	if (!is_5ghz && (nvm_flags & NVM_CHANNEL_40MHZ)) {
		if (ch_num <= LAST_2GHZ_HT_PLUS)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		if (ch_num >= FIRST_2GHZ_HT_MINUS)
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	} else if (ch_num <= last_5ghz_ht && (nvm_flags & NVM_CHANNEL_40MHZ)) {
		if ((ch_idx - NUM_2GHZ_CHANNELS) % 2 == 0)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		else
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	}
	if (!(nvm_flags & NVM_CHANNEL_80MHZ))
		flags |= IEEE80211_CHAN_NO_80MHZ;
	if (!(nvm_flags & NVM_CHANNEL_160MHZ))
		flags |= IEEE80211_CHAN_NO_160MHZ;

	if (!(nvm_flags & NVM_CHANNEL_IBSS))
		flags |= IEEE80211_CHAN_NO_IR;

	if (!(nvm_flags & NVM_CHANNEL_ACTIVE))
		flags |= IEEE80211_CHAN_NO_IR;

	if (nvm_flags & NVM_CHANNEL_RADAR)
		flags |= IEEE80211_CHAN_RADAR;

	if (nvm_flags & NVM_CHANNEL_INDOOR_ONLY)
		flags |= IEEE80211_CHAN_INDOOR_ONLY;

	/* Set the GO concurrent flag only in case that NO_IR is set.
	 * Otherwise it is meaningless
	 */
	if ((nvm_flags & NVM_CHANNEL_GO_CONCURRENT) &&
	    (flags & IEEE80211_CHAN_NO_IR))
		flags |= IEEE80211_CHAN_IR_CONCURRENT;

	return flags;
}