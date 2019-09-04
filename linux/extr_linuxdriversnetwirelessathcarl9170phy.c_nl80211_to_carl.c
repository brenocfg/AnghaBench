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
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
typedef  enum carl9170_bw { ____Placeholder_carl9170_bw } carl9170_bw ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CARL9170_BW_20 ; 
 int CARL9170_BW_40_ABOVE ; 
 int CARL9170_BW_40_BELOW ; 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 

__attribute__((used)) static enum carl9170_bw nl80211_to_carl(enum nl80211_channel_type type)
{
	switch (type) {
	case NL80211_CHAN_NO_HT:
	case NL80211_CHAN_HT20:
		return CARL9170_BW_20;
	case NL80211_CHAN_HT40MINUS:
		return CARL9170_BW_40_BELOW;
	case NL80211_CHAN_HT40PLUS:
		return CARL9170_BW_40_ABOVE;
	default:
		BUG();
	}
}