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
struct wireless_dev {int /*<<< orphan*/  conn_owner_nlportid; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  wiphy_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; } ;
struct cfg80211_external_auth_params {TYPE_1__ ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  action; int /*<<< orphan*/  key_mgmt_suite; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_ATTR_AKM_SUITES ; 
 int /*<<< orphan*/  NL80211_ATTR_BSSID ; 
 int /*<<< orphan*/  NL80211_ATTR_EXTERNAL_AUTH_ACTION ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_SSID ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_EXTERNAL_AUTH ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

int cfg80211_external_auth_request(struct net_device *dev,
				   struct cfg80211_external_auth_params *params,
				   gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct sk_buff *msg;
	void *hdr;

	if (!wdev->conn_owner_nlportid)
		return -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_EXTERNAL_AUTH);
	if (!hdr)
		goto nla_put_failure;

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex) ||
	    nla_put_u32(msg, NL80211_ATTR_AKM_SUITES, params->key_mgmt_suite) ||
	    nla_put_u32(msg, NL80211_ATTR_EXTERNAL_AUTH_ACTION,
			params->action) ||
	    nla_put(msg, NL80211_ATTR_BSSID, ETH_ALEN, params->bssid) ||
	    nla_put(msg, NL80211_ATTR_SSID, params->ssid.ssid_len,
		    params->ssid.ssid))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(&rdev->wiphy), msg,
			wdev->conn_owner_nlportid);
	return 0;

 nla_put_failure:
	nlmsg_free(msg);
	return -ENOBUFS;
}