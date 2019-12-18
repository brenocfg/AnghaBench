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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int ipvs_property; } ;
struct ip_vs_protocol {int dummy; } ;
struct ip_vs_conn {int flags; int /*<<< orphan*/  ipvs; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int AF_INET6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IP_VS_CONN_F_MASQ ; 
 int IP_VS_CONN_F_NFCT ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int,union nf_inet_addr*) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IP_VS_FWD_METHOD (struct ip_vs_conn*) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 scalar_t__ ip_vs_checksum_complete (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_nat_icmp (struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  ip_vs_nat_icmp_v6 (struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  ip_vs_notrack (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_vs_out_stats (struct ip_vs_conn*,struct sk_buff*) ; 
 scalar_t__ ip_vs_route_me_harder (int /*<<< orphan*/ ,int,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_update_conntrack (struct sk_buff*,struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_csum_unnecessary (struct sk_buff*) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int handle_response_icmp(int af, struct sk_buff *skb,
				union nf_inet_addr *snet,
				__u8 protocol, struct ip_vs_conn *cp,
				struct ip_vs_protocol *pp,
				unsigned int offset, unsigned int ihl,
				unsigned int hooknum)
{
	unsigned int verdict = NF_DROP;

	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		goto ignore_cp;

	/* Ensure the checksum is correct */
	if (!skb_csum_unnecessary(skb) && ip_vs_checksum_complete(skb, ihl)) {
		/* Failed checksum! */
		IP_VS_DBG_BUF(1, "Forward ICMP: failed checksum from %s!\n",
			      IP_VS_DBG_ADDR(af, snet));
		goto out;
	}

	if (IPPROTO_TCP == protocol || IPPROTO_UDP == protocol ||
	    IPPROTO_SCTP == protocol)
		offset += 2 * sizeof(__u16);
	if (skb_ensure_writable(skb, offset))
		goto out;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_nat_icmp_v6(skb, pp, cp, 1);
	else
#endif
		ip_vs_nat_icmp(skb, pp, cp, 1);

	if (ip_vs_route_me_harder(cp->ipvs, af, skb, hooknum))
		goto out;

	/* do the statistics and put it back */
	ip_vs_out_stats(cp, skb);

	skb->ipvs_property = 1;
	if (!(cp->flags & IP_VS_CONN_F_NFCT))
		ip_vs_notrack(skb);
	else
		ip_vs_update_conntrack(skb, cp, 0);

ignore_cp:
	verdict = NF_ACCEPT;

out:
	__ip_vs_conn_put(cp);

	return verdict;
}