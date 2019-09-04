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
typedef  int u32 ;
struct cfg80211_chan_def {int width; int center_freq1; TYPE_1__* chan; int /*<<< orphan*/  center_freq2; } ;
struct TYPE_2__ {int center_freq; } ;

/* Variables and functions */
 int IEEE80211_STA_DISABLE_160MHZ ; 
 int IEEE80211_STA_DISABLE_40MHZ ; 
 int IEEE80211_STA_DISABLE_80P80MHZ ; 
 int IEEE80211_STA_DISABLE_HT ; 
 int IEEE80211_STA_DISABLE_VHT ; 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 

u32 ieee80211_chandef_downgrade(struct cfg80211_chan_def *c)
{
	u32 ret;
	int tmp;

	switch (c->width) {
	case NL80211_CHAN_WIDTH_20:
		c->width = NL80211_CHAN_WIDTH_20_NOHT;
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		break;
	case NL80211_CHAN_WIDTH_40:
		c->width = NL80211_CHAN_WIDTH_20;
		c->center_freq1 = c->chan->center_freq;
		ret = IEEE80211_STA_DISABLE_40MHZ |
		      IEEE80211_STA_DISABLE_VHT;
		break;
	case NL80211_CHAN_WIDTH_80:
		tmp = (30 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		tmp /= 2;
		/* freq_P40 */
		c->center_freq1 = c->center_freq1 - 20 + 40 * tmp;
		c->width = NL80211_CHAN_WIDTH_40;
		ret = IEEE80211_STA_DISABLE_VHT;
		break;
	case NL80211_CHAN_WIDTH_80P80:
		c->center_freq2 = 0;
		c->width = NL80211_CHAN_WIDTH_80;
		ret = IEEE80211_STA_DISABLE_80P80MHZ |
		      IEEE80211_STA_DISABLE_160MHZ;
		break;
	case NL80211_CHAN_WIDTH_160:
		/* n_P20 */
		tmp = (70 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P80 */
		tmp /= 4;
		c->center_freq1 = c->center_freq1 - 40 + 80 * tmp;
		c->width = NL80211_CHAN_WIDTH_80;
		ret = IEEE80211_STA_DISABLE_80P80MHZ |
		      IEEE80211_STA_DISABLE_160MHZ;
		break;
	default:
	case NL80211_CHAN_WIDTH_20_NOHT:
		WARN_ON_ONCE(1);
		c->width = NL80211_CHAN_WIDTH_20_NOHT;
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		break;
	case NL80211_CHAN_WIDTH_5:
	case NL80211_CHAN_WIDTH_10:
		WARN_ON_ONCE(1);
		/* keep c->width */
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		break;
	}

	WARN_ON_ONCE(!cfg80211_chandef_valid(c));

	return ret;
}