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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_CQM_PKT_LOSS_EVENT ; 
 struct sk_buff* cfg80211_prepare_cqm (struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_send_cqm (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_cfg80211_cqm_pktloss_notify (struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void cfg80211_cqm_pktloss_notify(struct net_device *dev,
				 const u8 *peer, u32 num_packets, gfp_t gfp)
{
	struct sk_buff *msg;

	trace_cfg80211_cqm_pktloss_notify(dev, peer, num_packets);

	msg = cfg80211_prepare_cqm(dev, peer, gfp);
	if (!msg)
		return;

	if (nla_put_u32(msg, NL80211_ATTR_CQM_PKT_LOSS_EVENT, num_packets))
		goto nla_put_failure;

	cfg80211_send_cqm(msg, gfp);
	return;

 nla_put_failure:
	nlmsg_free(msg);
}