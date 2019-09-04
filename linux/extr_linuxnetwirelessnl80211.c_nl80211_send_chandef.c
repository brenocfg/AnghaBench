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
struct sk_buff {int dummy; } ;
struct cfg80211_chan_def {int width; int center_freq1; int center_freq2; TYPE_1__* chan; } ;
struct TYPE_2__ {int center_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NL80211_ATTR_CENTER_FREQ1 ; 
 int /*<<< orphan*/  NL80211_ATTR_CENTER_FREQ2 ; 
 int /*<<< orphan*/  NL80211_ATTR_CHANNEL_WIDTH ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY_CHANNEL_TYPE ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY_FREQ ; 
#define  NL80211_CHAN_WIDTH_20 130 
#define  NL80211_CHAN_WIDTH_20_NOHT 129 
#define  NL80211_CHAN_WIDTH_40 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def const*) ; 
 int cfg80211_get_chandef_type (struct cfg80211_chan_def const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nl80211_send_chandef(struct sk_buff *msg,
				const struct cfg80211_chan_def *chandef)
{
	if (WARN_ON(!cfg80211_chandef_valid(chandef)))
		return -EINVAL;

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ,
			chandef->chan->center_freq))
		return -ENOBUFS;
	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
	case NL80211_CHAN_WIDTH_40:
		if (nla_put_u32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE,
				cfg80211_get_chandef_type(chandef)))
			return -ENOBUFS;
		break;
	default:
		break;
	}
	if (nla_put_u32(msg, NL80211_ATTR_CHANNEL_WIDTH, chandef->width))
		return -ENOBUFS;
	if (nla_put_u32(msg, NL80211_ATTR_CENTER_FREQ1, chandef->center_freq1))
		return -ENOBUFS;
	if (chandef->center_freq2 &&
	    nla_put_u32(msg, NL80211_ATTR_CENTER_FREQ2, chandef->center_freq2))
		return -ENOBUFS;
	return 0;
}