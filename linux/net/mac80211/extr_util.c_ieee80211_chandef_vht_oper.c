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
struct ieee80211_vht_operation {int center_freq_seg0_idx; int center_freq_seg1_idx; int chan_width; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_ht_operation {int /*<<< orphan*/  operation_mode; } ;
struct cfg80211_chan_def {int center_freq1; int center_freq2; void* width; TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int IEEE80211_HT_OP_MODE_CCFS2_MASK ; 
 int IEEE80211_HT_OP_MODE_CCFS2_SHIFT ; 
#define  IEEE80211_VHT_CHANWIDTH_160MHZ 131 
#define  IEEE80211_VHT_CHANWIDTH_80MHZ 130 
#define  IEEE80211_VHT_CHANWIDTH_80P80MHZ 129 
#define  IEEE80211_VHT_CHANWIDTH_USE_HT 128 
 void* NL80211_CHAN_WIDTH_160 ; 
 void* NL80211_CHAN_WIDTH_80 ; 
 void* NL80211_CHAN_WIDTH_80P80 ; 
 int /*<<< orphan*/  SUPPORTS_VHT_EXT_NSS_BW ; 
 unsigned int abs (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 int ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

bool ieee80211_chandef_vht_oper(struct ieee80211_hw *hw,
				const struct ieee80211_vht_operation *oper,
				const struct ieee80211_ht_operation *htop,
				struct cfg80211_chan_def *chandef)
{
	struct cfg80211_chan_def new = *chandef;
	int cf0, cf1;
	int ccfs0, ccfs1, ccfs2;
	int ccf0, ccf1;

	if (!oper || !htop)
		return false;

	ccfs0 = oper->center_freq_seg0_idx;
	ccfs1 = oper->center_freq_seg1_idx;
	ccfs2 = (le16_to_cpu(htop->operation_mode) &
				IEEE80211_HT_OP_MODE_CCFS2_MASK)
			>> IEEE80211_HT_OP_MODE_CCFS2_SHIFT;

	/* when parsing (and we know how to) CCFS1 and CCFS2 are equivalent */
	ccf0 = ccfs0;
	ccf1 = ccfs1;
	if (!ccfs1 && ieee80211_hw_check(hw, SUPPORTS_VHT_EXT_NSS_BW))
		ccf1 = ccfs2;

	cf0 = ieee80211_channel_to_frequency(ccf0, chandef->chan->band);
	cf1 = ieee80211_channel_to_frequency(ccf1, chandef->chan->band);

	switch (oper->chan_width) {
	case IEEE80211_VHT_CHANWIDTH_USE_HT:
		/* just use HT information directly */
		break;
	case IEEE80211_VHT_CHANWIDTH_80MHZ:
		new.width = NL80211_CHAN_WIDTH_80;
		new.center_freq1 = cf0;
		/* If needed, adjust based on the newer interop workaround. */
		if (ccf1) {
			unsigned int diff;

			diff = abs(ccf1 - ccf0);
			if (diff == 8) {
				new.width = NL80211_CHAN_WIDTH_160;
				new.center_freq1 = cf1;
			} else if (diff > 8) {
				new.width = NL80211_CHAN_WIDTH_80P80;
				new.center_freq2 = cf1;
			}
		}
		break;
	case IEEE80211_VHT_CHANWIDTH_160MHZ:
		/* deprecated encoding */
		new.width = NL80211_CHAN_WIDTH_160;
		new.center_freq1 = cf0;
		break;
	case IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		/* deprecated encoding */
		new.width = NL80211_CHAN_WIDTH_80P80;
		new.center_freq1 = cf0;
		new.center_freq2 = cf1;
		break;
	default:
		return false;
	}

	if (!cfg80211_chandef_valid(&new))
		return false;

	*chandef = new;
	return true;
}