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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  protonum; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; } ;
struct nf_conn {int status; TYPE_1__* tuplehash; } ;
struct iphdr {int dummy; } ;
struct icmphdr {scalar_t__ type; scalar_t__ checksum; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_3__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CTINFO2DIR (int) ; 
 int HOOK2MANIP (unsigned int) ; 
 scalar_t__ ICMP_REDIRECT ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 unsigned long IPS_DST_NAT ; 
 int IPS_NAT_DONE_MASK ; 
 int IPS_NAT_MASK ; 
 unsigned long IPS_SRC_NAT ; 
 int IP_CT_DIR_REPLY ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_ipv4_manip_pkt (struct sk_buff*,unsigned int,struct nf_conntrack_tuple*,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

int nf_nat_icmp_reply_translation(struct sk_buff *skb,
				  struct nf_conn *ct,
				  enum ip_conntrack_info ctinfo,
				  unsigned int hooknum)
{
	struct {
		struct icmphdr	icmp;
		struct iphdr	ip;
	} *inside;
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	enum nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	unsigned int hdrlen = ip_hdrlen(skb);
	struct nf_conntrack_tuple target;
	unsigned long statusbit;

	WARN_ON(ctinfo != IP_CT_RELATED && ctinfo != IP_CT_RELATED_REPLY);

	if (skb_ensure_writable(skb, hdrlen + sizeof(*inside)))
		return 0;
	if (nf_ip_checksum(skb, hooknum, hdrlen, IPPROTO_ICMP))
		return 0;

	inside = (void *)skb->data + hdrlen;
	if (inside->icmp.type == ICMP_REDIRECT) {
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

	if (!nf_nat_ipv4_manip_pkt(skb, hdrlen + sizeof(inside->icmp),
				   &ct->tuplehash[!dir].tuple, !manip))
		return 0;

	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		/* Reloading "inside" here since manip_pkt may reallocate */
		inside = (void *)skb->data + hdrlen;
		inside->icmp.checksum = 0;
		inside->icmp.checksum =
			csum_fold(skb_checksum(skb, hdrlen,
					       skb->len - hdrlen, 0));
	}

	/* Change outer to look like the reply to an incoming packet */
	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);
	target.dst.protonum = IPPROTO_ICMP;
	if (!nf_nat_ipv4_manip_pkt(skb, 0, &target, manip))
		return 0;

	return 1;
}