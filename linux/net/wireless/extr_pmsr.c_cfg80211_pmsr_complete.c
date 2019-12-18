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
struct wireless_dev {int /*<<< orphan*/  pmsr_lock; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy_idx; } ;
struct cfg80211_pmsr_request {int /*<<< orphan*/  list; int /*<<< orphan*/  nl_portid; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_COOKIE ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_ATTR_WDEV ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_PEER_MEASUREMENT_COMPLETE ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_pmsr_request*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cfg80211_pmsr_complete (int /*<<< orphan*/ ,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_id (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void cfg80211_pmsr_complete(struct wireless_dev *wdev,
			    struct cfg80211_pmsr_request *req,
			    gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct sk_buff *msg;
	void *hdr;

	trace_cfg80211_pmsr_complete(wdev->wiphy, wdev, req->cookie);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		goto free_request;

	hdr = nl80211hdr_put(msg, 0, 0, 0,
			     NL80211_CMD_PEER_MEASUREMENT_COMPLETE);
	if (!hdr)
		goto free_msg;

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		goto free_msg;

	if (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, req->cookie,
			      NL80211_ATTR_PAD))
		goto free_msg;

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(wdev->wiphy), msg, req->nl_portid);
	goto free_request;
free_msg:
	nlmsg_free(msg);
free_request:
	spin_lock_bh(&wdev->pmsr_lock);
	list_del(&req->list);
	spin_unlock_bh(&wdev->pmsr_lock);
	kfree(req);
}