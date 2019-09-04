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
struct sk_buff {scalar_t__ cb; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_MCGRP_MLME ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfg80211_send_cqm(struct sk_buff *msg, gfp_t gfp)
{
	void **cb = (void **)msg->cb;
	struct cfg80211_registered_device *rdev = cb[2];

	nla_nest_end(msg, cb[1]);
	genlmsg_end(msg, cb[0]);

	memset(msg->cb, 0, sizeof(msg->cb));

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
}