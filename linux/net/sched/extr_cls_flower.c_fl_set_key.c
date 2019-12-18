#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_21__ {int /*<<< orphan*/  flags; void* addr_type; } ;
struct TYPE_20__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_19__ {scalar_t__ keyid; } ;
struct TYPE_18__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_17__ {void* addr_type; } ;
struct TYPE_16__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_30__ {scalar_t__ n_proto; scalar_t__ ip_proto; } ;
struct TYPE_29__ {scalar_t__ sip; scalar_t__ tip; scalar_t__ op; scalar_t__* sha; scalar_t__* tha; } ;
struct TYPE_28__ {scalar_t__ type; scalar_t__ code; } ;
struct TYPE_27__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_26__ {scalar_t__ flags; } ;
struct TYPE_25__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_24__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_23__ {scalar_t__* dst; scalar_t__* src; } ;
struct TYPE_22__ {int ingress_ifindex; } ;
struct fl_flow_key {TYPE_15__ control; int /*<<< orphan*/  ct; int /*<<< orphan*/  enc_ip; TYPE_14__ enc_tp; TYPE_13__ enc_key_id; TYPE_12__ enc_ipv6; TYPE_11__ enc_control; TYPE_10__ enc_ipv4; TYPE_9__ basic; TYPE_8__ arp; int /*<<< orphan*/  mpls; TYPE_7__ icmp; TYPE_6__ tp; TYPE_5__ tcp; TYPE_4__ ipv6; TYPE_3__ ipv4; int /*<<< orphan*/  ip; int /*<<< orphan*/  cvlan; int /*<<< orphan*/  vlan; TYPE_2__ eth; TYPE_1__ meta; } ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_MPLS_MC ; 
 int /*<<< orphan*/  ETH_P_MPLS_UC ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 void* FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 void* FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 size_t TCA_FLOWER_INDEV ; 
 size_t TCA_FLOWER_KEY_ARP_OP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_OP_MASK ; 
 size_t TCA_FLOWER_KEY_ARP_SHA ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SHA_MASK ; 
 size_t TCA_FLOWER_KEY_ARP_SIP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_SIP_MASK ; 
 size_t TCA_FLOWER_KEY_ARP_THA ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_THA_MASK ; 
 size_t TCA_FLOWER_KEY_ARP_TIP ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ARP_TIP_MASK ; 
 size_t TCA_FLOWER_KEY_CVLAN_ETH_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_CVLAN_ID ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_CVLAN_PRIO ; 
 size_t TCA_FLOWER_KEY_ENC_IPV4_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_DST_MASK ; 
 size_t TCA_FLOWER_KEY_ENC_IPV4_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_ENC_IPV6_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_DST_MASK ; 
 size_t TCA_FLOWER_KEY_ENC_IPV6_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_ENC_KEY_ID ; 
 size_t TCA_FLOWER_KEY_ENC_OPTS ; 
 size_t TCA_FLOWER_KEY_ENC_UDP_DST_PORT ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK ; 
 size_t TCA_FLOWER_KEY_ENC_UDP_SRC_PORT ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK ; 
 size_t TCA_FLOWER_KEY_ETH_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_DST_MASK ; 
 size_t TCA_FLOWER_KEY_ETH_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ETH_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_ETH_TYPE ; 
 size_t TCA_FLOWER_KEY_FLAGS ; 
 size_t TCA_FLOWER_KEY_ICMPV4_CODE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_CODE_MASK ; 
 size_t TCA_FLOWER_KEY_ICMPV4_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV4_TYPE_MASK ; 
 size_t TCA_FLOWER_KEY_ICMPV6_CODE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_CODE_MASK ; 
 size_t TCA_FLOWER_KEY_ICMPV6_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ICMPV6_TYPE_MASK ; 
 size_t TCA_FLOWER_KEY_IPV4_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_DST_MASK ; 
 size_t TCA_FLOWER_KEY_IPV4_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV4_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_IPV6_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_DST_MASK ; 
 size_t TCA_FLOWER_KEY_IPV6_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_IPV6_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_IP_PROTO ; 
 size_t TCA_FLOWER_KEY_SCTP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_DST_MASK ; 
 size_t TCA_FLOWER_KEY_SCTP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_SCTP_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_TCP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_DST_MASK ; 
 size_t TCA_FLOWER_KEY_TCP_FLAGS ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_FLAGS_MASK ; 
 size_t TCA_FLOWER_KEY_TCP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_TCP_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_UDP_DST ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_DST_MASK ; 
 size_t TCA_FLOWER_KEY_UDP_SRC ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_UDP_SRC_MASK ; 
 size_t TCA_FLOWER_KEY_VLAN_ETH_TYPE ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_VLAN_ID ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_VLAN_PRIO ; 
 int /*<<< orphan*/  TCA_FLOWER_UNSPEC ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_vlan (void*) ; 
 int fl_set_enc_opt (struct nlattr**,struct fl_flow_key*,struct fl_flow_key*,struct netlink_ext_ack*) ; 
 int fl_set_key_ct (struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int fl_set_key_flags (struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fl_set_key_ip (struct nlattr**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fl_set_key_mpls (struct nlattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fl_set_key_port_range (struct nlattr**,struct fl_flow_key*,struct fl_flow_key*) ; 
 int /*<<< orphan*/  fl_set_key_val (struct nlattr**,scalar_t__*,size_t,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fl_set_key_vlan (struct nlattr**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 void* nla_get_be16 (struct nlattr*) ; 
 int tcf_change_indev (struct net*,struct nlattr*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int fl_set_key(struct net *net, struct nlattr **tb,
		      struct fl_flow_key *key, struct fl_flow_key *mask,
		      struct netlink_ext_ack *extack)
{
	__be16 ethertype;
	int ret = 0;

	if (tb[TCA_FLOWER_INDEV]) {
		int err = tcf_change_indev(net, tb[TCA_FLOWER_INDEV], extack);
		if (err < 0)
			return err;
		key->meta.ingress_ifindex = err;
		mask->meta.ingress_ifindex = 0xffffffff;
	}

	fl_set_key_val(tb, key->eth.dst, TCA_FLOWER_KEY_ETH_DST,
		       mask->eth.dst, TCA_FLOWER_KEY_ETH_DST_MASK,
		       sizeof(key->eth.dst));
	fl_set_key_val(tb, key->eth.src, TCA_FLOWER_KEY_ETH_SRC,
		       mask->eth.src, TCA_FLOWER_KEY_ETH_SRC_MASK,
		       sizeof(key->eth.src));

	if (tb[TCA_FLOWER_KEY_ETH_TYPE]) {
		ethertype = nla_get_be16(tb[TCA_FLOWER_KEY_ETH_TYPE]);

		if (eth_type_vlan(ethertype)) {
			fl_set_key_vlan(tb, ethertype, TCA_FLOWER_KEY_VLAN_ID,
					TCA_FLOWER_KEY_VLAN_PRIO, &key->vlan,
					&mask->vlan);

			if (tb[TCA_FLOWER_KEY_VLAN_ETH_TYPE]) {
				ethertype = nla_get_be16(tb[TCA_FLOWER_KEY_VLAN_ETH_TYPE]);
				if (eth_type_vlan(ethertype)) {
					fl_set_key_vlan(tb, ethertype,
							TCA_FLOWER_KEY_CVLAN_ID,
							TCA_FLOWER_KEY_CVLAN_PRIO,
							&key->cvlan, &mask->cvlan);
					fl_set_key_val(tb, &key->basic.n_proto,
						       TCA_FLOWER_KEY_CVLAN_ETH_TYPE,
						       &mask->basic.n_proto,
						       TCA_FLOWER_UNSPEC,
						       sizeof(key->basic.n_proto));
				} else {
					key->basic.n_proto = ethertype;
					mask->basic.n_proto = cpu_to_be16(~0);
				}
			}
		} else {
			key->basic.n_proto = ethertype;
			mask->basic.n_proto = cpu_to_be16(~0);
		}
	}

	if (key->basic.n_proto == htons(ETH_P_IP) ||
	    key->basic.n_proto == htons(ETH_P_IPV6)) {
		fl_set_key_val(tb, &key->basic.ip_proto, TCA_FLOWER_KEY_IP_PROTO,
			       &mask->basic.ip_proto, TCA_FLOWER_UNSPEC,
			       sizeof(key->basic.ip_proto));
		fl_set_key_ip(tb, false, &key->ip, &mask->ip);
	}

	if (tb[TCA_FLOWER_KEY_IPV4_SRC] || tb[TCA_FLOWER_KEY_IPV4_DST]) {
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		mask->control.addr_type = ~0;
		fl_set_key_val(tb, &key->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC,
			       &mask->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC_MASK,
			       sizeof(key->ipv4.src));
		fl_set_key_val(tb, &key->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST,
			       &mask->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST_MASK,
			       sizeof(key->ipv4.dst));
	} else if (tb[TCA_FLOWER_KEY_IPV6_SRC] || tb[TCA_FLOWER_KEY_IPV6_DST]) {
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		mask->control.addr_type = ~0;
		fl_set_key_val(tb, &key->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC,
			       &mask->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC_MASK,
			       sizeof(key->ipv6.src));
		fl_set_key_val(tb, &key->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST,
			       &mask->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST_MASK,
			       sizeof(key->ipv6.dst));
	}

	if (key->basic.ip_proto == IPPROTO_TCP) {
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_TCP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_TCP_SRC_MASK,
			       sizeof(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_TCP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_TCP_DST_MASK,
			       sizeof(key->tp.dst));
		fl_set_key_val(tb, &key->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS,
			       &mask->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS_MASK,
			       sizeof(key->tcp.flags));
	} else if (key->basic.ip_proto == IPPROTO_UDP) {
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_UDP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_UDP_SRC_MASK,
			       sizeof(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_UDP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_UDP_DST_MASK,
			       sizeof(key->tp.dst));
	} else if (key->basic.ip_proto == IPPROTO_SCTP) {
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_SCTP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_SCTP_SRC_MASK,
			       sizeof(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_SCTP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_SCTP_DST_MASK,
			       sizeof(key->tp.dst));
	} else if (key->basic.n_proto == htons(ETH_P_IP) &&
		   key->basic.ip_proto == IPPROTO_ICMP) {
		fl_set_key_val(tb, &key->icmp.type, TCA_FLOWER_KEY_ICMPV4_TYPE,
			       &mask->icmp.type,
			       TCA_FLOWER_KEY_ICMPV4_TYPE_MASK,
			       sizeof(key->icmp.type));
		fl_set_key_val(tb, &key->icmp.code, TCA_FLOWER_KEY_ICMPV4_CODE,
			       &mask->icmp.code,
			       TCA_FLOWER_KEY_ICMPV4_CODE_MASK,
			       sizeof(key->icmp.code));
	} else if (key->basic.n_proto == htons(ETH_P_IPV6) &&
		   key->basic.ip_proto == IPPROTO_ICMPV6) {
		fl_set_key_val(tb, &key->icmp.type, TCA_FLOWER_KEY_ICMPV6_TYPE,
			       &mask->icmp.type,
			       TCA_FLOWER_KEY_ICMPV6_TYPE_MASK,
			       sizeof(key->icmp.type));
		fl_set_key_val(tb, &key->icmp.code, TCA_FLOWER_KEY_ICMPV6_CODE,
			       &mask->icmp.code,
			       TCA_FLOWER_KEY_ICMPV6_CODE_MASK,
			       sizeof(key->icmp.code));
	} else if (key->basic.n_proto == htons(ETH_P_MPLS_UC) ||
		   key->basic.n_proto == htons(ETH_P_MPLS_MC)) {
		ret = fl_set_key_mpls(tb, &key->mpls, &mask->mpls);
		if (ret)
			return ret;
	} else if (key->basic.n_proto == htons(ETH_P_ARP) ||
		   key->basic.n_proto == htons(ETH_P_RARP)) {
		fl_set_key_val(tb, &key->arp.sip, TCA_FLOWER_KEY_ARP_SIP,
			       &mask->arp.sip, TCA_FLOWER_KEY_ARP_SIP_MASK,
			       sizeof(key->arp.sip));
		fl_set_key_val(tb, &key->arp.tip, TCA_FLOWER_KEY_ARP_TIP,
			       &mask->arp.tip, TCA_FLOWER_KEY_ARP_TIP_MASK,
			       sizeof(key->arp.tip));
		fl_set_key_val(tb, &key->arp.op, TCA_FLOWER_KEY_ARP_OP,
			       &mask->arp.op, TCA_FLOWER_KEY_ARP_OP_MASK,
			       sizeof(key->arp.op));
		fl_set_key_val(tb, key->arp.sha, TCA_FLOWER_KEY_ARP_SHA,
			       mask->arp.sha, TCA_FLOWER_KEY_ARP_SHA_MASK,
			       sizeof(key->arp.sha));
		fl_set_key_val(tb, key->arp.tha, TCA_FLOWER_KEY_ARP_THA,
			       mask->arp.tha, TCA_FLOWER_KEY_ARP_THA_MASK,
			       sizeof(key->arp.tha));
	}

	if (key->basic.ip_proto == IPPROTO_TCP ||
	    key->basic.ip_proto == IPPROTO_UDP ||
	    key->basic.ip_proto == IPPROTO_SCTP) {
		ret = fl_set_key_port_range(tb, key, mask);
		if (ret)
			return ret;
	}

	if (tb[TCA_FLOWER_KEY_ENC_IPV4_SRC] ||
	    tb[TCA_FLOWER_KEY_ENC_IPV4_DST]) {
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		mask->enc_control.addr_type = ~0;
		fl_set_key_val(tb, &key->enc_ipv4.src,
			       TCA_FLOWER_KEY_ENC_IPV4_SRC,
			       &mask->enc_ipv4.src,
			       TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK,
			       sizeof(key->enc_ipv4.src));
		fl_set_key_val(tb, &key->enc_ipv4.dst,
			       TCA_FLOWER_KEY_ENC_IPV4_DST,
			       &mask->enc_ipv4.dst,
			       TCA_FLOWER_KEY_ENC_IPV4_DST_MASK,
			       sizeof(key->enc_ipv4.dst));
	}

	if (tb[TCA_FLOWER_KEY_ENC_IPV6_SRC] ||
	    tb[TCA_FLOWER_KEY_ENC_IPV6_DST]) {
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		mask->enc_control.addr_type = ~0;
		fl_set_key_val(tb, &key->enc_ipv6.src,
			       TCA_FLOWER_KEY_ENC_IPV6_SRC,
			       &mask->enc_ipv6.src,
			       TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK,
			       sizeof(key->enc_ipv6.src));
		fl_set_key_val(tb, &key->enc_ipv6.dst,
			       TCA_FLOWER_KEY_ENC_IPV6_DST,
			       &mask->enc_ipv6.dst,
			       TCA_FLOWER_KEY_ENC_IPV6_DST_MASK,
			       sizeof(key->enc_ipv6.dst));
	}

	fl_set_key_val(tb, &key->enc_key_id.keyid, TCA_FLOWER_KEY_ENC_KEY_ID,
		       &mask->enc_key_id.keyid, TCA_FLOWER_UNSPEC,
		       sizeof(key->enc_key_id.keyid));

	fl_set_key_val(tb, &key->enc_tp.src, TCA_FLOWER_KEY_ENC_UDP_SRC_PORT,
		       &mask->enc_tp.src, TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK,
		       sizeof(key->enc_tp.src));

	fl_set_key_val(tb, &key->enc_tp.dst, TCA_FLOWER_KEY_ENC_UDP_DST_PORT,
		       &mask->enc_tp.dst, TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK,
		       sizeof(key->enc_tp.dst));

	fl_set_key_ip(tb, true, &key->enc_ip, &mask->enc_ip);

	if (tb[TCA_FLOWER_KEY_ENC_OPTS]) {
		ret = fl_set_enc_opt(tb, key, mask, extack);
		if (ret)
			return ret;
	}

	ret = fl_set_key_ct(tb, &key->ct, &mask->ct, extack);
	if (ret)
		return ret;

	if (tb[TCA_FLOWER_KEY_FLAGS])
		ret = fl_set_key_flags(tb, &key->control.flags, &mask->control.flags);

	return ret;
}