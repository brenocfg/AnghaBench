#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_14__ {int /*<<< orphan*/  tll; int /*<<< orphan*/  sll; int /*<<< orphan*/  target; } ;
struct TYPE_19__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_15__ {TYPE_10__ nd; int /*<<< orphan*/  label; TYPE_2__ addr; } ;
struct TYPE_26__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; scalar_t__ flags; } ;
struct TYPE_25__ {scalar_t__ proto; scalar_t__ frag; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_16__ {scalar_t__ tci; } ;
struct TYPE_24__ {scalar_t__ type; TYPE_12__ cvlan; TYPE_12__ vlan; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_23__ {int /*<<< orphan*/  top_lse; } ;
struct TYPE_21__ {int /*<<< orphan*/  tha; int /*<<< orphan*/  sha; } ;
struct TYPE_20__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_22__ {TYPE_4__ arp; TYPE_3__ addr; } ;
struct TYPE_18__ {int priority; scalar_t__ in_port; int skb_mark; } ;
struct TYPE_17__ {int tun_flags; } ;
struct sw_flow_key {int recirc_id; int ovs_flow_hash; TYPE_11__ ipv6; TYPE_9__ tp; TYPE_8__ ip; TYPE_7__ eth; TYPE_6__ mpls; TYPE_5__ ipv4; int /*<<< orphan*/  nsh; TYPE_1__ phy; scalar_t__ tun_proto; int /*<<< orphan*/  tun_opts_len; TYPE_13__ tun_key; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_udp {int /*<<< orphan*/  udp_dst; int /*<<< orphan*/  udp_src; } ;
struct ovs_key_tcp {int /*<<< orphan*/  tcp_dst; int /*<<< orphan*/  tcp_src; } ;
struct ovs_key_sctp {int /*<<< orphan*/  sctp_dst; int /*<<< orphan*/  sctp_src; } ;
struct ovs_key_nd {int /*<<< orphan*/  nd_tll; int /*<<< orphan*/  nd_sll; int /*<<< orphan*/  nd_target; } ;
struct ovs_key_mpls {int /*<<< orphan*/  mpls_lse; } ;
struct ovs_key_ipv6 {scalar_t__ ipv6_proto; scalar_t__ ipv6_frag; int /*<<< orphan*/  ipv6_hlimit; int /*<<< orphan*/  ipv6_tclass; int /*<<< orphan*/  ipv6_label; int /*<<< orphan*/  ipv6_dst; int /*<<< orphan*/  ipv6_src; } ;
struct ovs_key_ipv4 {scalar_t__ ipv4_proto; scalar_t__ ipv4_frag; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv4_dst; int /*<<< orphan*/  ipv4_src; } ;
struct ovs_key_icmpv6 {scalar_t__ icmpv6_type; void* icmpv6_code; } ;
struct ovs_key_icmp {void* icmp_code; void* icmp_type; } ;
struct ovs_key_ethernet {int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; } ;
struct ovs_key_arp {int /*<<< orphan*/  arp_tha; int /*<<< orphan*/  arp_sha; scalar_t__ arp_op; int /*<<< orphan*/  arp_tip; int /*<<< orphan*/  arp_sip; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_MAX_PORTS ; 
 int EMSGSIZE ; 
 scalar_t__ ETH_P_802_2 ; 
 scalar_t__ ETH_P_ARP ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ ETH_P_NSH ; 
 scalar_t__ ETH_P_RARP ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ MAC_PROTO_ETHERNET ; 
 scalar_t__ NDISC_NEIGHBOUR_ADVERTISEMENT ; 
 scalar_t__ NDISC_NEIGHBOUR_SOLICITATION ; 
 scalar_t__ OVS_FRAG_TYPE_LATER ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ARP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_DP_HASH ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ENCAP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ETHERNET ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ETHERTYPE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ICMP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ICMPV6 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IN_PORT ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IPV4 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IPV6 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_MPLS ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ND ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_PRIORITY ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_RECIRC_ID ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_SCTP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_SKB_MARK ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_TCP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_TCP_FLAGS ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_UDP ; 
 int TUNNEL_OPTIONS_PRESENT ; 
 void* TUN_METADATA_OPTS (struct sw_flow_key const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ eth_p_mpls (scalar_t__) ; 
 scalar_t__ eth_type_vlan (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ ip_tun_to_nlattr (struct sk_buff*,TYPE_13__*,void const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ovs_key_arp*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nsh_key_to_nlattr (int /*<<< orphan*/ *,int,struct sk_buff*) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ ovs_ct_put_key (struct sw_flow_key const*,struct sw_flow_key const*,struct sk_buff*) ; 
 scalar_t__ ovs_key_mac_proto (struct sw_flow_key const*) ; 
 scalar_t__ ovs_nla_put_vlan (struct sk_buff*,TYPE_12__*,int) ; 

__attribute__((used)) static int __ovs_nla_put_key(const struct sw_flow_key *swkey,
			     const struct sw_flow_key *output, bool is_mask,
			     struct sk_buff *skb)
{
	struct ovs_key_ethernet *eth_key;
	struct nlattr *nla;
	struct nlattr *encap = NULL;
	struct nlattr *in_encap = NULL;

	if (nla_put_u32(skb, OVS_KEY_ATTR_RECIRC_ID, output->recirc_id))
		goto nla_put_failure;

	if (nla_put_u32(skb, OVS_KEY_ATTR_DP_HASH, output->ovs_flow_hash))
		goto nla_put_failure;

	if (nla_put_u32(skb, OVS_KEY_ATTR_PRIORITY, output->phy.priority))
		goto nla_put_failure;

	if ((swkey->tun_proto || is_mask)) {
		const void *opts = NULL;

		if (output->tun_key.tun_flags & TUNNEL_OPTIONS_PRESENT)
			opts = TUN_METADATA_OPTS(output, swkey->tun_opts_len);

		if (ip_tun_to_nlattr(skb, &output->tun_key, opts,
				     swkey->tun_opts_len, swkey->tun_proto, 0))
			goto nla_put_failure;
	}

	if (swkey->phy.in_port == DP_MAX_PORTS) {
		if (is_mask && (output->phy.in_port == 0xffff))
			if (nla_put_u32(skb, OVS_KEY_ATTR_IN_PORT, 0xffffffff))
				goto nla_put_failure;
	} else {
		u16 upper_u16;
		upper_u16 = !is_mask ? 0 : 0xffff;

		if (nla_put_u32(skb, OVS_KEY_ATTR_IN_PORT,
				(upper_u16 << 16) | output->phy.in_port))
			goto nla_put_failure;
	}

	if (nla_put_u32(skb, OVS_KEY_ATTR_SKB_MARK, output->phy.skb_mark))
		goto nla_put_failure;

	if (ovs_ct_put_key(swkey, output, skb))
		goto nla_put_failure;

	if (ovs_key_mac_proto(swkey) == MAC_PROTO_ETHERNET) {
		nla = nla_reserve(skb, OVS_KEY_ATTR_ETHERNET, sizeof(*eth_key));
		if (!nla)
			goto nla_put_failure;

		eth_key = nla_data(nla);
		ether_addr_copy(eth_key->eth_src, output->eth.src);
		ether_addr_copy(eth_key->eth_dst, output->eth.dst);

		if (swkey->eth.vlan.tci || eth_type_vlan(swkey->eth.type)) {
			if (ovs_nla_put_vlan(skb, &output->eth.vlan, is_mask))
				goto nla_put_failure;
			encap = nla_nest_start_noflag(skb, OVS_KEY_ATTR_ENCAP);
			if (!swkey->eth.vlan.tci)
				goto unencap;

			if (swkey->eth.cvlan.tci || eth_type_vlan(swkey->eth.type)) {
				if (ovs_nla_put_vlan(skb, &output->eth.cvlan, is_mask))
					goto nla_put_failure;
				in_encap = nla_nest_start_noflag(skb,
								 OVS_KEY_ATTR_ENCAP);
				if (!swkey->eth.cvlan.tci)
					goto unencap;
			}
		}

		if (swkey->eth.type == htons(ETH_P_802_2)) {
			/*
			* Ethertype 802.2 is represented in the netlink with omitted
			* OVS_KEY_ATTR_ETHERTYPE in the flow key attribute, and
			* 0xffff in the mask attribute.  Ethertype can also
			* be wildcarded.
			*/
			if (is_mask && output->eth.type)
				if (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE,
							output->eth.type))
					goto nla_put_failure;
			goto unencap;
		}
	}

	if (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, output->eth.type))
		goto nla_put_failure;

	if (eth_type_vlan(swkey->eth.type)) {
		/* There are 3 VLAN tags, we don't know anything about the rest
		 * of the packet, so truncate here.
		 */
		WARN_ON_ONCE(!(encap && in_encap));
		goto unencap;
	}

	if (swkey->eth.type == htons(ETH_P_IP)) {
		struct ovs_key_ipv4 *ipv4_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV4, sizeof(*ipv4_key));
		if (!nla)
			goto nla_put_failure;
		ipv4_key = nla_data(nla);
		ipv4_key->ipv4_src = output->ipv4.addr.src;
		ipv4_key->ipv4_dst = output->ipv4.addr.dst;
		ipv4_key->ipv4_proto = output->ip.proto;
		ipv4_key->ipv4_tos = output->ip.tos;
		ipv4_key->ipv4_ttl = output->ip.ttl;
		ipv4_key->ipv4_frag = output->ip.frag;
	} else if (swkey->eth.type == htons(ETH_P_IPV6)) {
		struct ovs_key_ipv6 *ipv6_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV6, sizeof(*ipv6_key));
		if (!nla)
			goto nla_put_failure;
		ipv6_key = nla_data(nla);
		memcpy(ipv6_key->ipv6_src, &output->ipv6.addr.src,
				sizeof(ipv6_key->ipv6_src));
		memcpy(ipv6_key->ipv6_dst, &output->ipv6.addr.dst,
				sizeof(ipv6_key->ipv6_dst));
		ipv6_key->ipv6_label = output->ipv6.label;
		ipv6_key->ipv6_proto = output->ip.proto;
		ipv6_key->ipv6_tclass = output->ip.tos;
		ipv6_key->ipv6_hlimit = output->ip.ttl;
		ipv6_key->ipv6_frag = output->ip.frag;
	} else if (swkey->eth.type == htons(ETH_P_NSH)) {
		if (nsh_key_to_nlattr(&output->nsh, is_mask, skb))
			goto nla_put_failure;
	} else if (swkey->eth.type == htons(ETH_P_ARP) ||
		   swkey->eth.type == htons(ETH_P_RARP)) {
		struct ovs_key_arp *arp_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_ARP, sizeof(*arp_key));
		if (!nla)
			goto nla_put_failure;
		arp_key = nla_data(nla);
		memset(arp_key, 0, sizeof(struct ovs_key_arp));
		arp_key->arp_sip = output->ipv4.addr.src;
		arp_key->arp_tip = output->ipv4.addr.dst;
		arp_key->arp_op = htons(output->ip.proto);
		ether_addr_copy(arp_key->arp_sha, output->ipv4.arp.sha);
		ether_addr_copy(arp_key->arp_tha, output->ipv4.arp.tha);
	} else if (eth_p_mpls(swkey->eth.type)) {
		struct ovs_key_mpls *mpls_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_MPLS, sizeof(*mpls_key));
		if (!nla)
			goto nla_put_failure;
		mpls_key = nla_data(nla);
		mpls_key->mpls_lse = output->mpls.top_lse;
	}

	if ((swkey->eth.type == htons(ETH_P_IP) ||
	     swkey->eth.type == htons(ETH_P_IPV6)) &&
	     swkey->ip.frag != OVS_FRAG_TYPE_LATER) {

		if (swkey->ip.proto == IPPROTO_TCP) {
			struct ovs_key_tcp *tcp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_TCP, sizeof(*tcp_key));
			if (!nla)
				goto nla_put_failure;
			tcp_key = nla_data(nla);
			tcp_key->tcp_src = output->tp.src;
			tcp_key->tcp_dst = output->tp.dst;
			if (nla_put_be16(skb, OVS_KEY_ATTR_TCP_FLAGS,
					 output->tp.flags))
				goto nla_put_failure;
		} else if (swkey->ip.proto == IPPROTO_UDP) {
			struct ovs_key_udp *udp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_UDP, sizeof(*udp_key));
			if (!nla)
				goto nla_put_failure;
			udp_key = nla_data(nla);
			udp_key->udp_src = output->tp.src;
			udp_key->udp_dst = output->tp.dst;
		} else if (swkey->ip.proto == IPPROTO_SCTP) {
			struct ovs_key_sctp *sctp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_SCTP, sizeof(*sctp_key));
			if (!nla)
				goto nla_put_failure;
			sctp_key = nla_data(nla);
			sctp_key->sctp_src = output->tp.src;
			sctp_key->sctp_dst = output->tp.dst;
		} else if (swkey->eth.type == htons(ETH_P_IP) &&
			   swkey->ip.proto == IPPROTO_ICMP) {
			struct ovs_key_icmp *icmp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMP, sizeof(*icmp_key));
			if (!nla)
				goto nla_put_failure;
			icmp_key = nla_data(nla);
			icmp_key->icmp_type = ntohs(output->tp.src);
			icmp_key->icmp_code = ntohs(output->tp.dst);
		} else if (swkey->eth.type == htons(ETH_P_IPV6) &&
			   swkey->ip.proto == IPPROTO_ICMPV6) {
			struct ovs_key_icmpv6 *icmpv6_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMPV6,
						sizeof(*icmpv6_key));
			if (!nla)
				goto nla_put_failure;
			icmpv6_key = nla_data(nla);
			icmpv6_key->icmpv6_type = ntohs(output->tp.src);
			icmpv6_key->icmpv6_code = ntohs(output->tp.dst);

			if (icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_SOLICITATION ||
			    icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_ADVERTISEMENT) {
				struct ovs_key_nd *nd_key;

				nla = nla_reserve(skb, OVS_KEY_ATTR_ND, sizeof(*nd_key));
				if (!nla)
					goto nla_put_failure;
				nd_key = nla_data(nla);
				memcpy(nd_key->nd_target, &output->ipv6.nd.target,
							sizeof(nd_key->nd_target));
				ether_addr_copy(nd_key->nd_sll, output->ipv6.nd.sll);
				ether_addr_copy(nd_key->nd_tll, output->ipv6.nd.tll);
			}
		}
	}

unencap:
	if (in_encap)
		nla_nest_end(skb, in_encap);
	if (encap)
		nla_nest_end(skb, encap);

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}