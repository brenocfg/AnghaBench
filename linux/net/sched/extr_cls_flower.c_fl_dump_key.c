#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct TYPE_21__ {scalar_t__ addr_type; int /*<<< orphan*/  flags; } ;
struct TYPE_20__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_19__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_18__ {scalar_t__ addr_type; } ;
struct TYPE_17__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_31__ {scalar_t__ n_proto; scalar_t__ ip_proto; } ;
struct TYPE_30__ {scalar_t__ sip; scalar_t__ tip; scalar_t__ op; scalar_t__* sha; scalar_t__* tha; } ;
struct TYPE_29__ {scalar_t__ type; scalar_t__ code; } ;
struct TYPE_28__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_27__ {scalar_t__ flags; } ;
struct TYPE_26__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_25__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_22__ {scalar_t__ vlan_tpid; } ;
struct TYPE_24__ {scalar_t__* dst; scalar_t__* src; } ;
struct TYPE_23__ {scalar_t__ ingress_ifindex; } ;
struct fl_flow_key {scalar_t__ enc_key_id; TYPE_14__ control; int /*<<< orphan*/  ct; int /*<<< orphan*/  enc_opts; int /*<<< orphan*/  enc_ip; TYPE_13__ enc_tp; TYPE_12__ enc_ipv6; TYPE_11__ enc_control; TYPE_10__ enc_ipv4; TYPE_9__ basic; TYPE_8__ arp; TYPE_7__ icmp; TYPE_6__ tp; TYPE_5__ tcp; TYPE_4__ ipv6; TYPE_3__ ipv4; int /*<<< orphan*/  ip; TYPE_15__ vlan; TYPE_15__ cvlan; int /*<<< orphan*/  mpls; TYPE_2__ eth; TYPE_1__ meta; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  TCA_FLOWER_INDEV ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_OP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_OP_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SHA ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SHA_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SIP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SIP_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_THA ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_THA_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_TIP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_TIP_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_CVLAN_ETH_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_CVLAN_ID ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_CVLAN_PRIO ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_KEY_ID ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_DST_PORT ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_SRC_PORT ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_CODE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_CODE_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_TYPE_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_CODE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_CODE_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_TYPE_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IP_PROTO ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_FLAGS ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_FLAGS_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_DST_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_SRC_MASK ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_VLAN_ETH_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_VLAN_ID ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_VLAN_PRIO ; 
 int /*<<< orphan*/  TCA_FLOWER_UNSPEC ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 scalar_t__ fl_dump_key_ct (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fl_dump_key_enc_opt (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fl_dump_key_flags (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fl_dump_key_ip (struct sk_buff*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fl_dump_key_mpls (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fl_dump_key_port_range (struct sk_buff*,struct fl_flow_key*,struct fl_flow_key*) ; 
 scalar_t__ fl_dump_key_val (struct sk_buff*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fl_dump_key_vlan (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,TYPE_15__*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_dump_key(struct sk_buff *skb, struct net *net,
		       struct fl_flow_key *key, struct fl_flow_key *mask)
{
	if (mask->meta.ingress_ifindex) {
		struct net_device *dev;

		dev = __dev_get_by_index(net, key->meta.ingress_ifindex);
		if (dev && nla_put_string(skb, TCA_FLOWER_INDEV, dev->name))
			goto nla_put_failure;
	}

	if (fl_dump_key_val(skb, key->eth.dst, TCA_FLOWER_KEY_ETH_DST,
			    mask->eth.dst, TCA_FLOWER_KEY_ETH_DST_MASK,
			    sizeof(key->eth.dst)) ||
	    fl_dump_key_val(skb, key->eth.src, TCA_FLOWER_KEY_ETH_SRC,
			    mask->eth.src, TCA_FLOWER_KEY_ETH_SRC_MASK,
			    sizeof(key->eth.src)) ||
	    fl_dump_key_val(skb, &key->basic.n_proto, TCA_FLOWER_KEY_ETH_TYPE,
			    &mask->basic.n_proto, TCA_FLOWER_UNSPEC,
			    sizeof(key->basic.n_proto)))
		goto nla_put_failure;

	if (fl_dump_key_mpls(skb, &key->mpls, &mask->mpls))
		goto nla_put_failure;

	if (fl_dump_key_vlan(skb, TCA_FLOWER_KEY_VLAN_ID,
			     TCA_FLOWER_KEY_VLAN_PRIO, &key->vlan, &mask->vlan))
		goto nla_put_failure;

	if (fl_dump_key_vlan(skb, TCA_FLOWER_KEY_CVLAN_ID,
			     TCA_FLOWER_KEY_CVLAN_PRIO,
			     &key->cvlan, &mask->cvlan) ||
	    (mask->cvlan.vlan_tpid &&
	     nla_put_be16(skb, TCA_FLOWER_KEY_VLAN_ETH_TYPE,
			  key->cvlan.vlan_tpid)))
		goto nla_put_failure;

	if (mask->basic.n_proto) {
		if (mask->cvlan.vlan_tpid) {
			if (nla_put_be16(skb, TCA_FLOWER_KEY_CVLAN_ETH_TYPE,
					 key->basic.n_proto))
				goto nla_put_failure;
		} else if (mask->vlan.vlan_tpid) {
			if (nla_put_be16(skb, TCA_FLOWER_KEY_VLAN_ETH_TYPE,
					 key->basic.n_proto))
				goto nla_put_failure;
		}
	}

	if ((key->basic.n_proto == htons(ETH_P_IP) ||
	     key->basic.n_proto == htons(ETH_P_IPV6)) &&
	    (fl_dump_key_val(skb, &key->basic.ip_proto, TCA_FLOWER_KEY_IP_PROTO,
			    &mask->basic.ip_proto, TCA_FLOWER_UNSPEC,
			    sizeof(key->basic.ip_proto)) ||
	    fl_dump_key_ip(skb, false, &key->ip, &mask->ip)))
		goto nla_put_failure;

	if (key->control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS &&
	    (fl_dump_key_val(skb, &key->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC,
			     &mask->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC_MASK,
			     sizeof(key->ipv4.src)) ||
	     fl_dump_key_val(skb, &key->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST,
			     &mask->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST_MASK,
			     sizeof(key->ipv4.dst))))
		goto nla_put_failure;
	else if (key->control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS &&
		 (fl_dump_key_val(skb, &key->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC,
				  &mask->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC_MASK,
				  sizeof(key->ipv6.src)) ||
		  fl_dump_key_val(skb, &key->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST,
				  &mask->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST_MASK,
				  sizeof(key->ipv6.dst))))
		goto nla_put_failure;

	if (key->basic.ip_proto == IPPROTO_TCP &&
	    (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_TCP_SRC,
			     &mask->tp.src, TCA_FLOWER_KEY_TCP_SRC_MASK,
			     sizeof(key->tp.src)) ||
	     fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_TCP_DST,
			     &mask->tp.dst, TCA_FLOWER_KEY_TCP_DST_MASK,
			     sizeof(key->tp.dst)) ||
	     fl_dump_key_val(skb, &key->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS,
			     &mask->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS_MASK,
			     sizeof(key->tcp.flags))))
		goto nla_put_failure;
	else if (key->basic.ip_proto == IPPROTO_UDP &&
		 (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_UDP_SRC,
				  &mask->tp.src, TCA_FLOWER_KEY_UDP_SRC_MASK,
				  sizeof(key->tp.src)) ||
		  fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_UDP_DST,
				  &mask->tp.dst, TCA_FLOWER_KEY_UDP_DST_MASK,
				  sizeof(key->tp.dst))))
		goto nla_put_failure;
	else if (key->basic.ip_proto == IPPROTO_SCTP &&
		 (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_SCTP_SRC,
				  &mask->tp.src, TCA_FLOWER_KEY_SCTP_SRC_MASK,
				  sizeof(key->tp.src)) ||
		  fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_SCTP_DST,
				  &mask->tp.dst, TCA_FLOWER_KEY_SCTP_DST_MASK,
				  sizeof(key->tp.dst))))
		goto nla_put_failure;
	else if (key->basic.n_proto == htons(ETH_P_IP) &&
		 key->basic.ip_proto == IPPROTO_ICMP &&
		 (fl_dump_key_val(skb, &key->icmp.type,
				  TCA_FLOWER_KEY_ICMPV4_TYPE, &mask->icmp.type,
				  TCA_FLOWER_KEY_ICMPV4_TYPE_MASK,
				  sizeof(key->icmp.type)) ||
		  fl_dump_key_val(skb, &key->icmp.code,
				  TCA_FLOWER_KEY_ICMPV4_CODE, &mask->icmp.code,
				  TCA_FLOWER_KEY_ICMPV4_CODE_MASK,
				  sizeof(key->icmp.code))))
		goto nla_put_failure;
	else if (key->basic.n_proto == htons(ETH_P_IPV6) &&
		 key->basic.ip_proto == IPPROTO_ICMPV6 &&
		 (fl_dump_key_val(skb, &key->icmp.type,
				  TCA_FLOWER_KEY_ICMPV6_TYPE, &mask->icmp.type,
				  TCA_FLOWER_KEY_ICMPV6_TYPE_MASK,
				  sizeof(key->icmp.type)) ||
		  fl_dump_key_val(skb, &key->icmp.code,
				  TCA_FLOWER_KEY_ICMPV6_CODE, &mask->icmp.code,
				  TCA_FLOWER_KEY_ICMPV6_CODE_MASK,
				  sizeof(key->icmp.code))))
		goto nla_put_failure;
	else if ((key->basic.n_proto == htons(ETH_P_ARP) ||
		  key->basic.n_proto == htons(ETH_P_RARP)) &&
		 (fl_dump_key_val(skb, &key->arp.sip,
				  TCA_FLOWER_KEY_ARP_SIP, &mask->arp.sip,
				  TCA_FLOWER_KEY_ARP_SIP_MASK,
				  sizeof(key->arp.sip)) ||
		  fl_dump_key_val(skb, &key->arp.tip,
				  TCA_FLOWER_KEY_ARP_TIP, &mask->arp.tip,
				  TCA_FLOWER_KEY_ARP_TIP_MASK,
				  sizeof(key->arp.tip)) ||
		  fl_dump_key_val(skb, &key->arp.op,
				  TCA_FLOWER_KEY_ARP_OP, &mask->arp.op,
				  TCA_FLOWER_KEY_ARP_OP_MASK,
				  sizeof(key->arp.op)) ||
		  fl_dump_key_val(skb, key->arp.sha, TCA_FLOWER_KEY_ARP_SHA,
				  mask->arp.sha, TCA_FLOWER_KEY_ARP_SHA_MASK,
				  sizeof(key->arp.sha)) ||
		  fl_dump_key_val(skb, key->arp.tha, TCA_FLOWER_KEY_ARP_THA,
				  mask->arp.tha, TCA_FLOWER_KEY_ARP_THA_MASK,
				  sizeof(key->arp.tha))))
		goto nla_put_failure;

	if ((key->basic.ip_proto == IPPROTO_TCP ||
	     key->basic.ip_proto == IPPROTO_UDP ||
	     key->basic.ip_proto == IPPROTO_SCTP) &&
	     fl_dump_key_port_range(skb, key, mask))
		goto nla_put_failure;

	if (key->enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS &&
	    (fl_dump_key_val(skb, &key->enc_ipv4.src,
			    TCA_FLOWER_KEY_ENC_IPV4_SRC, &mask->enc_ipv4.src,
			    TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK,
			    sizeof(key->enc_ipv4.src)) ||
	     fl_dump_key_val(skb, &key->enc_ipv4.dst,
			     TCA_FLOWER_KEY_ENC_IPV4_DST, &mask->enc_ipv4.dst,
			     TCA_FLOWER_KEY_ENC_IPV4_DST_MASK,
			     sizeof(key->enc_ipv4.dst))))
		goto nla_put_failure;
	else if (key->enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS &&
		 (fl_dump_key_val(skb, &key->enc_ipv6.src,
			    TCA_FLOWER_KEY_ENC_IPV6_SRC, &mask->enc_ipv6.src,
			    TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK,
			    sizeof(key->enc_ipv6.src)) ||
		 fl_dump_key_val(skb, &key->enc_ipv6.dst,
				 TCA_FLOWER_KEY_ENC_IPV6_DST,
				 &mask->enc_ipv6.dst,
				 TCA_FLOWER_KEY_ENC_IPV6_DST_MASK,
			    sizeof(key->enc_ipv6.dst))))
		goto nla_put_failure;

	if (fl_dump_key_val(skb, &key->enc_key_id, TCA_FLOWER_KEY_ENC_KEY_ID,
			    &mask->enc_key_id, TCA_FLOWER_UNSPEC,
			    sizeof(key->enc_key_id)) ||
	    fl_dump_key_val(skb, &key->enc_tp.src,
			    TCA_FLOWER_KEY_ENC_UDP_SRC_PORT,
			    &mask->enc_tp.src,
			    TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK,
			    sizeof(key->enc_tp.src)) ||
	    fl_dump_key_val(skb, &key->enc_tp.dst,
			    TCA_FLOWER_KEY_ENC_UDP_DST_PORT,
			    &mask->enc_tp.dst,
			    TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK,
			    sizeof(key->enc_tp.dst)) ||
	    fl_dump_key_ip(skb, true, &key->enc_ip, &mask->enc_ip) ||
	    fl_dump_key_enc_opt(skb, &key->enc_opts, &mask->enc_opts))
		goto nla_put_failure;

	if (fl_dump_key_ct(skb, &key->ct, &mask->ct))
		goto nla_put_failure;

	if (fl_dump_key_flags(skb, key->control.flags, mask->control.flags))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}