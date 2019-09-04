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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct cfg80211_sched_scan_request {int /*<<< orphan*/  reqid; TYPE_1__* dev; int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NL80211_ATTR_COOKIE ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nl80211_prep_sched_scan_msg(struct sk_buff *msg,
			    struct cfg80211_sched_scan_request *req, u32 cmd)
{
	void *hdr;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	if (!hdr)
		return -1;

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY,
			wiphy_to_rdev(req->wiphy)->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, req->dev->ifindex) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, req->reqid,
			      NL80211_ATTR_PAD))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}