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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int nexthdr; int /*<<< orphan*/  payload_len; } ;
struct ipv6_opt_hdr {int nexthdr; } ;

/* Variables and functions */
#define  IPPROTO_ICMPV6 136 
#define  IPPROTO_SCTP 135 
#define  IPPROTO_TCP 134 
#define  IPPROTO_UDP 133 
#define  IPPROTO_UDPLITE 132 
#define  NEXTHDR_DEST 131 
#define  NEXTHDR_FRAGMENT 130 
#define  NEXTHDR_HOP 129 
#define  NEXTHDR_ROUTING 128 
 int TCA_CSUM_UPDATE_FLAG_ICMP ; 
 int TCA_CSUM_UPDATE_FLAG_SCTP ; 
 int TCA_CSUM_UPDATE_FLAG_TCP ; 
 int TCA_CSUM_UPDATE_FLAG_UDP ; 
 int TCA_CSUM_UPDATE_FLAG_UDPLITE ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 unsigned int ipv6_optlen (struct ipv6_opt_hdr*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_csum_ipv6_hopopts (struct ipv6_opt_hdr*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  tcf_csum_ipv6_icmp (struct sk_buff*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tcf_csum_ipv6_tcp (struct sk_buff*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tcf_csum_ipv6_udp (struct sk_buff*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  tcf_csum_sctp (struct sk_buff*,unsigned int,unsigned int) ; 

__attribute__((used)) static int tcf_csum_ipv6(struct sk_buff *skb, u32 update_flags)
{
	struct ipv6hdr *ip6h;
	struct ipv6_opt_hdr *ip6xh;
	unsigned int hl, ixhl;
	unsigned int pl;
	int ntkoff;
	u8 nexthdr;

	ntkoff = skb_network_offset(skb);

	hl = sizeof(*ip6h);

	if (!pskb_may_pull(skb, hl + ntkoff))
		goto fail;

	ip6h = ipv6_hdr(skb);

	pl = ntohs(ip6h->payload_len);
	nexthdr = ip6h->nexthdr;

	do {
		switch (nexthdr) {
		case NEXTHDR_FRAGMENT:
			goto ignore_skb;
		case NEXTHDR_ROUTING:
		case NEXTHDR_HOP:
		case NEXTHDR_DEST:
			if (!pskb_may_pull(skb, hl + sizeof(*ip6xh) + ntkoff))
				goto fail;
			ip6xh = (void *)(skb_network_header(skb) + hl);
			ixhl = ipv6_optlen(ip6xh);
			if (!pskb_may_pull(skb, hl + ixhl + ntkoff))
				goto fail;
			ip6xh = (void *)(skb_network_header(skb) + hl);
			if ((nexthdr == NEXTHDR_HOP) &&
			    !(tcf_csum_ipv6_hopopts(ip6xh, ixhl, &pl)))
				goto fail;
			nexthdr = ip6xh->nexthdr;
			hl += ixhl;
			break;
		case IPPROTO_ICMPV6:
			if (update_flags & TCA_CSUM_UPDATE_FLAG_ICMP)
				if (!tcf_csum_ipv6_icmp(skb,
							hl, pl + sizeof(*ip6h)))
					goto fail;
			goto done;
		case IPPROTO_TCP:
			if (update_flags & TCA_CSUM_UPDATE_FLAG_TCP)
				if (!tcf_csum_ipv6_tcp(skb,
						       hl, pl + sizeof(*ip6h)))
					goto fail;
			goto done;
		case IPPROTO_UDP:
			if (update_flags & TCA_CSUM_UPDATE_FLAG_UDP)
				if (!tcf_csum_ipv6_udp(skb, hl,
						       pl + sizeof(*ip6h), 0))
					goto fail;
			goto done;
		case IPPROTO_UDPLITE:
			if (update_flags & TCA_CSUM_UPDATE_FLAG_UDPLITE)
				if (!tcf_csum_ipv6_udp(skb, hl,
						       pl + sizeof(*ip6h), 1))
					goto fail;
			goto done;
		case IPPROTO_SCTP:
			if ((update_flags & TCA_CSUM_UPDATE_FLAG_SCTP) &&
			    !tcf_csum_sctp(skb, hl, pl + sizeof(*ip6h)))
				goto fail;
			goto done;
		default:
			goto ignore_skb;
		}
	} while (pskb_may_pull(skb, hl + 1 + ntkoff));

done:
ignore_skb:
	return 1;

fail:
	return 0;
}