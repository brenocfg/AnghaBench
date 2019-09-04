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
struct ieee80211_ht_operation {int ht_param; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  chan; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;

/* Variables and functions */
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 130 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 129 
#define  IEEE80211_HT_PARAM_CHA_SEC_NONE 128 
 int IEEE80211_HT_PARAM_CHA_SEC_OFFSET ; 
 int NL80211_CHAN_HT20 ; 
 int NL80211_CHAN_HT40MINUS ; 
 int NL80211_CHAN_HT40PLUS ; 
 int NL80211_CHAN_NO_HT ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,int /*<<< orphan*/ ,int) ; 

bool ieee80211_chandef_ht_oper(const struct ieee80211_ht_operation *ht_oper,
			       struct cfg80211_chan_def *chandef)
{
	enum nl80211_channel_type channel_type;

	if (!ht_oper)
		return false;

	switch (ht_oper->ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) {
	case IEEE80211_HT_PARAM_CHA_SEC_NONE:
		channel_type = NL80211_CHAN_HT20;
		break;
	case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		channel_type = NL80211_CHAN_HT40PLUS;
		break;
	case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		channel_type = NL80211_CHAN_HT40MINUS;
		break;
	default:
		channel_type = NL80211_CHAN_NO_HT;
		return false;
	}

	cfg80211_chandef_create(chandef, chandef->chan, channel_type);
	return true;
}