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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct iphdr {int frag_off; int protocol; int ihl; int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 133 
#define  IPPROTO_IGMP 132 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int /*<<< orphan*/  IP_OFFSET ; 
 int TCA_CSUM_UPDATE_FLAG_ICMP ; 
 int TCA_CSUM_UPDATE_FLAG_IGMP ; 
 int TCA_CSUM_UPDATE_FLAG_IPV4HDR ; 
 int TCA_CSUM_UPDATE_FLAG_SCTP ; 
 int TCA_CSUM_UPDATE_FLAG_TCP ; 
 int TCA_CSUM_UPDATE_FLAG_UDP ; 
 int TCA_CSUM_UPDATE_FLAG_UDPLITE ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_try_make_writable (struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcf_csum_ipv4_icmp (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_csum_ipv4_igmp (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_csum_ipv4_tcp (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_csum_ipv4_udp (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcf_csum_sctp (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcf_csum_ipv4(struct sk_buff *skb, u32 update_flags)
{
	const struct iphdr *iph;
	int ntkoff;

	ntkoff = skb_network_offset(skb);

	if (!pskb_may_pull(skb, sizeof(*iph) + ntkoff))
		goto fail;

	iph = ip_hdr(skb);

	switch (iph->frag_off & htons(IP_OFFSET) ? 0 : iph->protocol) {
	case IPPROTO_ICMP:
		if (update_flags & TCA_CSUM_UPDATE_FLAG_ICMP)
			if (!tcf_csum_ipv4_icmp(skb, iph->ihl * 4,
						ntohs(iph->tot_len)))
				goto fail;
		break;
	case IPPROTO_IGMP:
		if (update_flags & TCA_CSUM_UPDATE_FLAG_IGMP)
			if (!tcf_csum_ipv4_igmp(skb, iph->ihl * 4,
						ntohs(iph->tot_len)))
				goto fail;
		break;
	case IPPROTO_TCP:
		if (update_flags & TCA_CSUM_UPDATE_FLAG_TCP)
			if (!tcf_csum_ipv4_tcp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len)))
				goto fail;
		break;
	case IPPROTO_UDP:
		if (update_flags & TCA_CSUM_UPDATE_FLAG_UDP)
			if (!tcf_csum_ipv4_udp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len), 0))
				goto fail;
		break;
	case IPPROTO_UDPLITE:
		if (update_flags & TCA_CSUM_UPDATE_FLAG_UDPLITE)
			if (!tcf_csum_ipv4_udp(skb, iph->ihl * 4,
					       ntohs(iph->tot_len), 1))
				goto fail;
		break;
	case IPPROTO_SCTP:
		if ((update_flags & TCA_CSUM_UPDATE_FLAG_SCTP) &&
		    !tcf_csum_sctp(skb, iph->ihl * 4, ntohs(iph->tot_len)))
			goto fail;
		break;
	}

	if (update_flags & TCA_CSUM_UPDATE_FLAG_IPV4HDR) {
		if (skb_try_make_writable(skb, sizeof(*iph) + ntkoff))
			goto fail;

		ip_send_check(ip_hdr(skb));
	}

	return 1;

fail:
	return 0;
}