#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nft_traceinfo {int type; int packet_dumped; TYPE_5__* basechain; TYPE_7__* verdict; TYPE_4__* chain; struct nft_pktinfo* pkt; } ;
struct nft_pktinfo {TYPE_6__* skb; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_14__ {TYPE_1__* chain; } ;
struct TYPE_13__ {int mark; } ;
struct TYPE_12__ {int policy; TYPE_2__* type; } ;
struct TYPE_11__ {TYPE_3__* table; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  family; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNLGRP_NFTRACE ; 
 int /*<<< orphan*/  NFNL_SUBSYS_NFTABLES ; 
 int /*<<< orphan*/  NFTA_TRACE_CHAIN ; 
 int /*<<< orphan*/  NFTA_TRACE_MARK ; 
 int /*<<< orphan*/  NFTA_TRACE_NFPROTO ; 
 int /*<<< orphan*/  NFTA_TRACE_POLICY ; 
 int /*<<< orphan*/  NFTA_TRACE_TABLE ; 
 int /*<<< orphan*/  NFTA_TRACE_TYPE ; 
 int /*<<< orphan*/  NFTA_TRACE_VERDICT ; 
 int /*<<< orphan*/  NFT_MSG_TRACE ; 
 int NFT_TRACETYPE_LL_HSIZE ; 
 int NFT_TRACETYPE_NETWORK_HSIZE ; 
#define  NFT_TRACETYPE_POLICY 132 
#define  NFT_TRACETYPE_RETURN 131 
#define  NFT_TRACETYPE_RULE 130 
 int NFT_TRACETYPE_TRANSPORT_HSIZE ; 
#define  NFT_TRACETYPE_UNSPEC 129 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  __NFT_TRACETYPE_MAX 128 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nf_trace_fill_dev_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_trace_fill_pkt_info (struct sk_buff*,struct nft_pktinfo const*) ; 
 scalar_t__ nf_trace_fill_rule_info (struct sk_buff*,struct nft_traceinfo*) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_msg_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_in (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_out (struct nft_pktinfo const*) ; 
 int nft_pf (struct nft_pktinfo const*) ; 
 scalar_t__ nft_trace_have_verdict_chain (struct nft_traceinfo*) ; 
 int /*<<< orphan*/  nft_verdict_dump (struct sk_buff*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nla_total_size (int) ; 
 unsigned int nla_total_size_64bit (int) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (unsigned int,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int nlmsg_total_size (int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_fill_id (struct sk_buff*,TYPE_6__*) ; 

void nft_trace_notify(struct nft_traceinfo *info)
{
	const struct nft_pktinfo *pkt = info->pkt;
	struct nfgenmsg *nfmsg;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	unsigned int size;
	u16 event;

	if (!nfnetlink_has_listeners(nft_net(pkt), NFNLGRP_NFTRACE))
		return;

	size = nlmsg_total_size(sizeof(struct nfgenmsg)) +
		nla_total_size(strlen(info->chain->table->name)) +
		nla_total_size(strlen(info->chain->name)) +
		nla_total_size_64bit(sizeof(__be64)) +	/* rule handle */
		nla_total_size(sizeof(__be32)) +	/* trace type */
		nla_total_size(0) +			/* VERDICT, nested */
			nla_total_size(sizeof(u32)) +	/* verdict code */
		nla_total_size(sizeof(u32)) +		/* id */
		nla_total_size(NFT_TRACETYPE_LL_HSIZE) +
		nla_total_size(NFT_TRACETYPE_NETWORK_HSIZE) +
		nla_total_size(NFT_TRACETYPE_TRANSPORT_HSIZE) +
		nla_total_size(sizeof(u32)) +		/* iif */
		nla_total_size(sizeof(__be16)) +	/* iiftype */
		nla_total_size(sizeof(u32)) +		/* oif */
		nla_total_size(sizeof(__be16)) +	/* oiftype */
		nla_total_size(sizeof(u32)) +		/* mark */
		nla_total_size(sizeof(u32)) +		/* nfproto */
		nla_total_size(sizeof(u32));		/* policy */

	if (nft_trace_have_verdict_chain(info))
		size += nla_total_size(strlen(info->verdict->chain->name)); /* jump target */

	skb = nlmsg_new(size, GFP_ATOMIC);
	if (!skb)
		return;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, NFT_MSG_TRACE);
	nlh = nlmsg_put(skb, 0, 0, event, sizeof(struct nfgenmsg), 0);
	if (!nlh)
		goto nla_put_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family	= info->basechain->type->family;
	nfmsg->version		= NFNETLINK_V0;
	nfmsg->res_id		= 0;

	if (nla_put_be32(skb, NFTA_TRACE_NFPROTO, htonl(nft_pf(pkt))))
		goto nla_put_failure;

	if (nla_put_be32(skb, NFTA_TRACE_TYPE, htonl(info->type)))
		goto nla_put_failure;

	if (trace_fill_id(skb, pkt->skb))
		goto nla_put_failure;

	if (nla_put_string(skb, NFTA_TRACE_CHAIN, info->chain->name))
		goto nla_put_failure;

	if (nla_put_string(skb, NFTA_TRACE_TABLE, info->chain->table->name))
		goto nla_put_failure;

	if (nf_trace_fill_rule_info(skb, info))
		goto nla_put_failure;

	switch (info->type) {
	case NFT_TRACETYPE_UNSPEC:
	case __NFT_TRACETYPE_MAX:
		break;
	case NFT_TRACETYPE_RETURN:
	case NFT_TRACETYPE_RULE:
		if (nft_verdict_dump(skb, NFTA_TRACE_VERDICT, info->verdict))
			goto nla_put_failure;
		break;
	case NFT_TRACETYPE_POLICY:
		if (nla_put_be32(skb, NFTA_TRACE_POLICY,
				 htonl(info->basechain->policy)))
			goto nla_put_failure;
		break;
	}

	if (pkt->skb->mark &&
	    nla_put_be32(skb, NFTA_TRACE_MARK, htonl(pkt->skb->mark)))
		goto nla_put_failure;

	if (!info->packet_dumped) {
		if (nf_trace_fill_dev_info(skb, nft_in(pkt), nft_out(pkt)))
			goto nla_put_failure;

		if (nf_trace_fill_pkt_info(skb, pkt))
			goto nla_put_failure;
		info->packet_dumped = true;
	}

	nlmsg_end(skb, nlh);
	nfnetlink_send(skb, nft_net(pkt), 0, NFNLGRP_NFTRACE, 0, GFP_ATOMIC);
	return;

 nla_put_failure:
	WARN_ON_ONCE(1);
	kfree_skb(skb);
}