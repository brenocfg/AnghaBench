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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; scalar_t__ data; } ;
struct nf_nat_l4proto {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int status; TYPE_1__* tuplehash; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; } ;
struct icmp6hdr {scalar_t__ icmp6_type; scalar_t__ icmp6_cksum; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_2__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CTINFO2DIR (int) ; 
 int HOOK2MANIP (unsigned int) ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 unsigned long IPS_DST_NAT ; 
 int IPS_NAT_DONE_MASK ; 
 int IPS_NAT_MASK ; 
 unsigned long IPS_SRC_NAT ; 
 int IP_CT_DIR_REPLY ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 scalar_t__ NDISC_REDIRECT ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nf_nat_l4proto* __nf_nat_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuplepr (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 scalar_t__ nf_ip6_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_ipv6_manip_pkt (struct sk_buff*,unsigned int,struct nf_nat_l4proto const*,struct nf_conntrack_tuple*,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 

int nf_nat_icmpv6_reply_translation(struct sk_buff *skb,
				    struct nf_conn *ct,
				    enum ip_conntrack_info ctinfo,
				    unsigned int hooknum,
				    unsigned int hdrlen)
{
	struct {
		struct icmp6hdr	icmp6;
		struct ipv6hdr	ip6;
	} *inside;
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	enum nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	const struct nf_nat_l4proto *l4proto;
	struct nf_conntrack_tuple target;
	unsigned long statusbit;

	WARN_ON(ctinfo != IP_CT_RELATED && ctinfo != IP_CT_RELATED_REPLY);

	if (!skb_make_writable(skb, hdrlen + sizeof(*inside)))
		return 0;
	if (nf_ip6_checksum(skb, hooknum, hdrlen, IPPROTO_ICMPV6))
		return 0;

	inside = (void *)skb->data + hdrlen;
	if (inside->icmp6.icmp6_type == NDISC_REDIRECT) {
		if ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			return 0;
		if (ct->status & IPS_NAT_MASK)
			return 0;
	}

	if (manip == NF_NAT_MANIP_SRC)
		statusbit = IPS_SRC_NAT;
	else
		statusbit = IPS_DST_NAT;

	/* Invert if this is reply direction */
	if (dir == IP_CT_DIR_REPLY)
		statusbit ^= IPS_NAT_MASK;

	if (!(ct->status & statusbit))
		return 1;

	l4proto = __nf_nat_l4proto_find(NFPROTO_IPV6, inside->ip6.nexthdr);
	if (!nf_nat_ipv6_manip_pkt(skb, hdrlen + sizeof(inside->icmp6),
				   l4proto, &ct->tuplehash[!dir].tuple, !manip))
		return 0;

	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		struct ipv6hdr *ipv6h = ipv6_hdr(skb);
		inside = (void *)skb->data + hdrlen;
		inside->icmp6.icmp6_cksum = 0;
		inside->icmp6.icmp6_cksum =
			csum_ipv6_magic(&ipv6h->saddr, &ipv6h->daddr,
					skb->len - hdrlen, IPPROTO_ICMPV6,
					skb_checksum(skb, hdrlen,
						     skb->len - hdrlen, 0));
	}

	nf_ct_invert_tuplepr(&target, &ct->tuplehash[!dir].tuple);
	l4proto = __nf_nat_l4proto_find(NFPROTO_IPV6, IPPROTO_ICMPV6);
	if (!nf_nat_ipv6_manip_pkt(skb, 0, l4proto, &target, manip))
		return 0;

	return 1;
}