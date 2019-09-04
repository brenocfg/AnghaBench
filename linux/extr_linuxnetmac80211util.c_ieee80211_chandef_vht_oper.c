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
struct ieee80211_vht_operation {int chan_width; scalar_t__ center_freq_seg0_idx; scalar_t__ center_freq_seg1_idx; } ;
struct cfg80211_chan_def {int center_freq1; int center_freq2; void* width; TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
#define  IEEE80211_VHT_CHANWIDTH_160MHZ 131 
#define  IEEE80211_VHT_CHANWIDTH_80MHZ 130 
#define  IEEE80211_VHT_CHANWIDTH_80P80MHZ 129 
#define  IEEE80211_VHT_CHANWIDTH_USE_HT 128 
 void* NL80211_CHAN_WIDTH_160 ; 
 void* NL80211_CHAN_WIDTH_80 ; 
 void* NL80211_CHAN_WIDTH_80P80 ; 
 unsigned int abs (scalar_t__) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 int ieee80211_channel_to_frequency (scalar_t__,int /*<<< orphan*/ ) ; 

bool ieee80211_chandef_vht_oper(const struct ieee80211_vht_operation *oper,
				struct cfg80211_chan_def *chandef)
{
	struct cfg80211_chan_def new = *chandef;
	int cf1, cf2;

	if (!oper)
		return false;

	cf1 = ieee80211_channel_to_frequency(oper->center_freq_seg0_idx,
					     chandef->chan->band);
	cf2 = ieee80211_channel_to_frequency(oper->center_freq_seg1_idx,
					     chandef->chan->band);

	switch (oper->chan_width) {
	case IEEE80211_VHT_CHANWIDTH_USE_HT:
		break;
	case IEEE80211_VHT_CHANWIDTH_80MHZ:
		new.width = NL80211_CHAN_WIDTH_80;
		new.center_freq1 = cf1;
		/* If needed, adjust based on the newer interop workaround. */
		if (oper->center_freq_seg1_idx) {
			unsigned int diff;

			diff = abs(oper->center_freq_seg1_idx -
				   oper->center_freq_seg0_idx);
			if (diff == 8) {
				new.width = NL80211_CHAN_WIDTH_160;
				new.center_freq1 = cf2;
			} else if (diff > 8) {
				new.width = NL80211_CHAN_WIDTH_80P80;
				new.center_freq2 = cf2;
			}
		}
		break;
	case IEEE80211_VHT_CHANWIDTH_160MHZ:
		new.width = NL80211_CHAN_WIDTH_160;
		new.center_freq1 = cf1;
		break;
	case IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		new.width = NL80211_CHAN_WIDTH_80P80;
		new.center_freq1 = cf1;
		new.center_freq2 = cf2;
		break;
	default:
		return false;
	}

	if (!cfg80211_chandef_valid(&new))
		return false;

	*chandef = new;
	return true;
}