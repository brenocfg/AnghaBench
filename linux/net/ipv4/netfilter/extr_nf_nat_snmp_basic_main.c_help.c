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
struct udphdr {scalar_t__ source; scalar_t__ dest; int /*<<< orphan*/  len; } ;
struct sk_buff {int len; } ;
struct nf_conn {int status; } ;
struct iphdr {int ihl; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int IPS_NAT_MASK ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_DIR_REPLY ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  SNMP_PORT ; 
 int /*<<< orphan*/  SNMP_TRAP_PORT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int) ; 
 int /*<<< orphan*/  snmp_lock ; 
 unsigned int snmp_translate (struct nf_conn*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int help(struct sk_buff *skb, unsigned int protoff,
		struct nf_conn *ct,
		enum ip_conntrack_info ctinfo)
{
	int dir = CTINFO2DIR(ctinfo);
	unsigned int ret;
	const struct iphdr *iph = ip_hdr(skb);
	const struct udphdr *udph = (struct udphdr *)((__be32 *)iph + iph->ihl);

	/* SNMP replies and originating SNMP traps get mangled */
	if (udph->source == htons(SNMP_PORT) && dir != IP_CT_DIR_REPLY)
		return NF_ACCEPT;
	if (udph->dest == htons(SNMP_TRAP_PORT) && dir != IP_CT_DIR_ORIGINAL)
		return NF_ACCEPT;

	/* No NAT? */
	if (!(ct->status & IPS_NAT_MASK))
		return NF_ACCEPT;

	/* Make sure the packet length is ok.  So far, we were only guaranteed
	 * to have a valid length IP header plus 8 bytes, which means we have
	 * enough room for a UDP header.  Just verify the UDP length field so we
	 * can mess around with the payload.
	 */
	if (ntohs(udph->len) != skb->len - (iph->ihl << 2)) {
		nf_ct_helper_log(skb, ct, "dropping malformed packet\n");
		return NF_DROP;
	}

	if (skb_ensure_writable(skb, skb->len)) {
		nf_ct_helper_log(skb, ct, "cannot mangle packet");
		return NF_DROP;
	}

	spin_lock_bh(&snmp_lock);
	ret = snmp_translate(ct, dir, skb);
	spin_unlock_bh(&snmp_lock);
	return ret;
}