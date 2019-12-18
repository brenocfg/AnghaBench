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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; scalar_t__ rtm_flags; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_table; scalar_t__ rtm_tos; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int dummy; } ;
struct mr_table {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int mfc_flags; } ;
struct mfc_cache {TYPE_1__ _c; int /*<<< orphan*/  mfc_mcastgrp; int /*<<< orphan*/  mfc_origin; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOENT ; 
 int MFC_STATIC ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_SRC ; 
 int /*<<< orphan*/  RTA_TABLE ; 
 int /*<<< orphan*/  RTNL_FAMILY_IPMR ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 int /*<<< orphan*/  RTPROT_MROUTED ; 
 int /*<<< orphan*/  RTPROT_STATIC ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int mr_fill_mroute (struct mr_table*,struct sk_buff*,TYPE_1__*,struct rtmsg*) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int ipmr_fill_mroute(struct mr_table *mrt, struct sk_buff *skb,
			    u32 portid, u32 seq, struct mfc_cache *c, int cmd,
			    int flags)
{
	struct nlmsghdr *nlh;
	struct rtmsg *rtm;
	int err;

	nlh = nlmsg_put(skb, portid, seq, cmd, sizeof(*rtm), flags);
	if (!nlh)
		return -EMSGSIZE;

	rtm = nlmsg_data(nlh);
	rtm->rtm_family   = RTNL_FAMILY_IPMR;
	rtm->rtm_dst_len  = 32;
	rtm->rtm_src_len  = 32;
	rtm->rtm_tos      = 0;
	rtm->rtm_table    = mrt->id;
	if (nla_put_u32(skb, RTA_TABLE, mrt->id))
		goto nla_put_failure;
	rtm->rtm_type     = RTN_MULTICAST;
	rtm->rtm_scope    = RT_SCOPE_UNIVERSE;
	if (c->_c.mfc_flags & MFC_STATIC)
		rtm->rtm_protocol = RTPROT_STATIC;
	else
		rtm->rtm_protocol = RTPROT_MROUTED;
	rtm->rtm_flags    = 0;

	if (nla_put_in_addr(skb, RTA_SRC, c->mfc_origin) ||
	    nla_put_in_addr(skb, RTA_DST, c->mfc_mcastgrp))
		goto nla_put_failure;
	err = mr_fill_mroute(mrt, skb, &c->_c, rtm);
	/* do not break the dump if cache is unresolved */
	if (err < 0 && err != -ENOENT)
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}