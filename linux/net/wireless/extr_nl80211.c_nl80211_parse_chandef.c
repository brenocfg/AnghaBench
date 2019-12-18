#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct genl_info {struct nlattr** attrs; struct netlink_ext_ack* extack; } ;
struct TYPE_8__ {int flags; } ;
struct cfg80211_registered_device {TYPE_3__ wiphy; } ;
struct TYPE_6__ {void* channels; void* bw_config; } ;
struct cfg80211_chan_def {scalar_t__ width; void* center_freq1; TYPE_1__ edmg; void* center_freq2; TYPE_2__* chan; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_CHAN_DISABLED ; 
 size_t NL80211_ATTR_CENTER_FREQ1 ; 
 size_t NL80211_ATTR_CENTER_FREQ2 ; 
 size_t NL80211_ATTR_CHANNEL_WIDTH ; 
 size_t NL80211_ATTR_WIPHY_CHANNEL_TYPE ; 
 size_t NL80211_ATTR_WIPHY_EDMG_BW_CONFIG ; 
 size_t NL80211_ATTR_WIPHY_EDMG_CHANNELS ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 
 scalar_t__ NL80211_CHAN_WIDTH_10 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr*,char*) ; 
 int WIPHY_FLAG_SUPPORTS_5_10_MHZ ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  cfg80211_chandef_usable (TYPE_3__*,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 TYPE_2__* ieee80211_get_channel (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  memset (struct cfg80211_chan_def*,int /*<<< orphan*/ ,int) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 

int nl80211_parse_chandef(struct cfg80211_registered_device *rdev,
			  struct genl_info *info,
			  struct cfg80211_chan_def *chandef)
{
	struct netlink_ext_ack *extack = info->extack;
	struct nlattr **attrs = info->attrs;
	u32 control_freq;

	if (!attrs[NL80211_ATTR_WIPHY_FREQ])
		return -EINVAL;

	control_freq = nla_get_u32(attrs[NL80211_ATTR_WIPHY_FREQ]);

	memset(chandef, 0, sizeof(*chandef));

	chandef->chan = ieee80211_get_channel(&rdev->wiphy, control_freq);
	chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
	chandef->center_freq1 = control_freq;
	chandef->center_freq2 = 0;

	/* Primary channel not allowed */
	if (!chandef->chan || chandef->chan->flags & IEEE80211_CHAN_DISABLED) {
		NL_SET_ERR_MSG_ATTR(extack, attrs[NL80211_ATTR_WIPHY_FREQ],
				    "Channel is disabled");
		return -EINVAL;
	}

	if (attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]) {
		enum nl80211_channel_type chantype;

		chantype = nla_get_u32(attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]);

		switch (chantype) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
		case NL80211_CHAN_HT40PLUS:
		case NL80211_CHAN_HT40MINUS:
			cfg80211_chandef_create(chandef, chandef->chan,
						chantype);
			/* user input for center_freq is incorrect */
			if (attrs[NL80211_ATTR_CENTER_FREQ1] &&
			    chandef->center_freq1 != nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ1])) {
				NL_SET_ERR_MSG_ATTR(extack,
						    attrs[NL80211_ATTR_CENTER_FREQ1],
						    "bad center frequency 1");
				return -EINVAL;
			}
			/* center_freq2 must be zero */
			if (attrs[NL80211_ATTR_CENTER_FREQ2] &&
			    nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ2])) {
				NL_SET_ERR_MSG_ATTR(extack,
						    attrs[NL80211_ATTR_CENTER_FREQ2],
						    "center frequency 2 can't be used");
				return -EINVAL;
			}
			break;
		default:
			NL_SET_ERR_MSG_ATTR(extack,
					    attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE],
					    "invalid channel type");
			return -EINVAL;
		}
	} else if (attrs[NL80211_ATTR_CHANNEL_WIDTH]) {
		chandef->width =
			nla_get_u32(attrs[NL80211_ATTR_CHANNEL_WIDTH]);
		if (attrs[NL80211_ATTR_CENTER_FREQ1])
			chandef->center_freq1 =
				nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ1]);
		if (attrs[NL80211_ATTR_CENTER_FREQ2])
			chandef->center_freq2 =
				nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ2]);
	}

	if (info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]) {
		chandef->edmg.channels =
		      nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]);

		if (info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG])
			chandef->edmg.bw_config =
		     nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG]);
	} else {
		chandef->edmg.bw_config = 0;
		chandef->edmg.channels = 0;
	}

	if (!cfg80211_chandef_valid(chandef)) {
		NL_SET_ERR_MSG(extack, "invalid channel definition");
		return -EINVAL;
	}

	if (!cfg80211_chandef_usable(&rdev->wiphy, chandef,
				     IEEE80211_CHAN_DISABLED)) {
		NL_SET_ERR_MSG(extack, "(extension) channel is disabled");
		return -EINVAL;
	}

	if ((chandef->width == NL80211_CHAN_WIDTH_5 ||
	     chandef->width == NL80211_CHAN_WIDTH_10) &&
	    !(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_5_10_MHZ)) {
		NL_SET_ERR_MSG(extack, "5/10 MHz not supported");
		return -EINVAL;
	}

	return 0;
}