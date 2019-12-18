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
struct TYPE_4__ {int channels; int bw_config; } ;
struct cfg80211_chan_def {TYPE_2__ edmg; TYPE_1__* chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  IEEE80211_EDMG_BW_CONFIG_10 139 
#define  IEEE80211_EDMG_BW_CONFIG_11 138 
#define  IEEE80211_EDMG_BW_CONFIG_12 137 
#define  IEEE80211_EDMG_BW_CONFIG_13 136 
#define  IEEE80211_EDMG_BW_CONFIG_14 135 
#define  IEEE80211_EDMG_BW_CONFIG_15 134 
#define  IEEE80211_EDMG_BW_CONFIG_4 133 
#define  IEEE80211_EDMG_BW_CONFIG_5 132 
#define  IEEE80211_EDMG_BW_CONFIG_6 131 
#define  IEEE80211_EDMG_BW_CONFIG_7 130 
#define  IEEE80211_EDMG_BW_CONFIG_8 129 
#define  IEEE80211_EDMG_BW_CONFIG_9 128 
 int /*<<< orphan*/  cfg80211_valid_60g_freq (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

__attribute__((used)) static bool cfg80211_edmg_chandef_valid(const struct cfg80211_chan_def *chandef)
{
	int max_contiguous = 0;
	int num_of_enabled = 0;
	int contiguous = 0;
	int i;

	if (!chandef->edmg.channels || !chandef->edmg.bw_config)
		return false;

	if (!cfg80211_valid_60g_freq(chandef->chan->center_freq))
		return false;

	for (i = 0; i < 6; i++) {
		if (chandef->edmg.channels & BIT(i)) {
			contiguous++;
			num_of_enabled++;
		} else {
			contiguous = 0;
		}

		max_contiguous = max(contiguous, max_contiguous);
	}
	/* basic verification of edmg configuration according to
	 * IEEE P802.11ay/D4.0 section 9.4.2.251
	 */
	/* check bw_config against contiguous edmg channels */
	switch (chandef->edmg.bw_config) {
	case IEEE80211_EDMG_BW_CONFIG_4:
	case IEEE80211_EDMG_BW_CONFIG_8:
	case IEEE80211_EDMG_BW_CONFIG_12:
		if (max_contiguous < 1)
			return false;
		break;
	case IEEE80211_EDMG_BW_CONFIG_5:
	case IEEE80211_EDMG_BW_CONFIG_9:
	case IEEE80211_EDMG_BW_CONFIG_13:
		if (max_contiguous < 2)
			return false;
		break;
	case IEEE80211_EDMG_BW_CONFIG_6:
	case IEEE80211_EDMG_BW_CONFIG_10:
	case IEEE80211_EDMG_BW_CONFIG_14:
		if (max_contiguous < 3)
			return false;
		break;
	case IEEE80211_EDMG_BW_CONFIG_7:
	case IEEE80211_EDMG_BW_CONFIG_11:
	case IEEE80211_EDMG_BW_CONFIG_15:
		if (max_contiguous < 4)
			return false;
		break;

	default:
		return false;
	}

	/* check bw_config against aggregated (non contiguous) edmg channels */
	switch (chandef->edmg.bw_config) {
	case IEEE80211_EDMG_BW_CONFIG_4:
	case IEEE80211_EDMG_BW_CONFIG_5:
	case IEEE80211_EDMG_BW_CONFIG_6:
	case IEEE80211_EDMG_BW_CONFIG_7:
		break;
	case IEEE80211_EDMG_BW_CONFIG_8:
	case IEEE80211_EDMG_BW_CONFIG_9:
	case IEEE80211_EDMG_BW_CONFIG_10:
	case IEEE80211_EDMG_BW_CONFIG_11:
		if (num_of_enabled < 2)
			return false;
		break;
	case IEEE80211_EDMG_BW_CONFIG_12:
	case IEEE80211_EDMG_BW_CONFIG_13:
	case IEEE80211_EDMG_BW_CONFIG_14:
	case IEEE80211_EDMG_BW_CONFIG_15:
		if (num_of_enabled < 4 || max_contiguous < 2)
			return false;
		break;
	default:
		return false;
	}

	return true;
}