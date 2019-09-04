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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wireless_dev {scalar_t__ current_bss; } ;
struct wiphy {int features; } ;
struct nlattr {int dummy; } ;
struct cfg80211_sched_scan_request {int flags; int /*<<< orphan*/ * mac_addr_mask; int /*<<< orphan*/ * mac_addr; } ;
struct cfg80211_scan_request {int flags; int /*<<< orphan*/ * mac_addr_mask; int /*<<< orphan*/ * mac_addr; } ;
typedef  enum nl80211_feature_flags { ____Placeholder_nl80211_feature_flags } nl80211_feature_flags ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_SCAN_FLAGS ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_HIGH_ACCURACY_SCAN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_LOW_POWER_SCAN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_LOW_SPAN_SCAN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCAN_RANDOM_SN ; 
 int NL80211_FEATURE_LOW_PRIORITY_SCAN ; 
 int NL80211_FEATURE_ND_RANDOM_MAC_ADDR ; 
 int NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR ; 
 int NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_HIGH_ACCURACY ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_LOW_POWER ; 
 int NL80211_SCAN_FLAG_LOW_PRIORITY ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_LOW_SPAN ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_MIN_PREQ_CONTENT ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE ; 
 int NL80211_SCAN_FLAG_RANDOM_ADDR ; 
 int /*<<< orphan*/  NL80211_SCAN_FLAG_RANDOM_SN ; 
 int /*<<< orphan*/  nl80211_check_scan_feat (struct wiphy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nl80211_parse_random_mac (struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int
nl80211_check_scan_flags(struct wiphy *wiphy, struct wireless_dev *wdev,
			 void *request, struct nlattr **attrs,
			 bool is_sched_scan)
{
	u8 *mac_addr, *mac_addr_mask;
	u32 *flags;
	enum nl80211_feature_flags randomness_flag;

	if (!attrs[NL80211_ATTR_SCAN_FLAGS])
		return 0;

	if (is_sched_scan) {
		struct cfg80211_sched_scan_request *req = request;

		randomness_flag = wdev ?
				  NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR :
				  NL80211_FEATURE_ND_RANDOM_MAC_ADDR;
		flags = &req->flags;
		mac_addr = req->mac_addr;
		mac_addr_mask = req->mac_addr_mask;
	} else {
		struct cfg80211_scan_request *req = request;

		randomness_flag = NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;
		flags = &req->flags;
		mac_addr = req->mac_addr;
		mac_addr_mask = req->mac_addr_mask;
	}

	*flags = nla_get_u32(attrs[NL80211_ATTR_SCAN_FLAGS]);

	if (((*flags & NL80211_SCAN_FLAG_LOW_PRIORITY) &&
	     !(wiphy->features & NL80211_FEATURE_LOW_PRIORITY_SCAN)) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_LOW_SPAN,
				     NL80211_EXT_FEATURE_LOW_SPAN_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_LOW_POWER,
				     NL80211_EXT_FEATURE_LOW_POWER_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_HIGH_ACCURACY,
				     NL80211_EXT_FEATURE_HIGH_ACCURACY_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME,
				     NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP,
				     NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION,
				     NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE,
				     NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_RANDOM_SN,
				     NL80211_EXT_FEATURE_SCAN_RANDOM_SN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_MIN_PREQ_CONTENT,
				     NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT))
		return -EOPNOTSUPP;

	if (*flags & NL80211_SCAN_FLAG_RANDOM_ADDR) {
		int err;

		if (!(wiphy->features & randomness_flag) ||
		    (wdev && wdev->current_bss))
			return -EOPNOTSUPP;

		err = nl80211_parse_random_mac(attrs, mac_addr, mac_addr_mask);
		if (err)
			return err;
	}

	return 0;
}