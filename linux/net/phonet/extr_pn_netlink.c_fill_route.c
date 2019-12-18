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
struct rtmsg {int rtm_dst_len; scalar_t__ rtm_flags; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_table; scalar_t__ rtm_tos; scalar_t__ rtm_src_len; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PHONET ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  RTPROT_STATIC ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_route(struct sk_buff *skb, struct net_device *dev, u8 dst,
			u32 portid, u32 seq, int event)
{
	struct rtmsg *rtm;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*rtm), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	rtm = nlmsg_data(nlh);
	rtm->rtm_family = AF_PHONET;
	rtm->rtm_dst_len = 6;
	rtm->rtm_src_len = 0;
	rtm->rtm_tos = 0;
	rtm->rtm_table = RT_TABLE_MAIN;
	rtm->rtm_protocol = RTPROT_STATIC;
	rtm->rtm_scope = RT_SCOPE_UNIVERSE;
	rtm->rtm_type = RTN_UNICAST;
	rtm->rtm_flags = 0;
	if (nla_put_u8(skb, RTA_DST, dst) ||
	    nla_put_u32(skb, RTA_OIF, dev->ifindex))
		goto nla_put_failure;
	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}