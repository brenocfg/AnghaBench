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
struct udphdr {int /*<<< orphan*/  check; } ;
struct tcphdr {int /*<<< orphan*/  check; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct ipv6hdr {int nexthdr; } ;
struct ila_params {int dummy; } ;
struct icmp6hdr {int /*<<< orphan*/  icmp6_cksum; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CSUM_MANGLED_0 ; 
#define  NEXTHDR_ICMP 130 
#define  NEXTHDR_TCP 129 
#define  NEXTHDR_UDP 128 
 int /*<<< orphan*/  get_csum_diff (struct ipv6hdr*,struct ila_params*) ; 
 int /*<<< orphan*/  inet_proto_csum_replace_by_diff (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static void ila_csum_adjust_transport(struct sk_buff *skb,
				      struct ila_params *p)
{
	size_t nhoff = sizeof(struct ipv6hdr);
	struct ipv6hdr *ip6h = ipv6_hdr(skb);
	__wsum diff;

	switch (ip6h->nexthdr) {
	case NEXTHDR_TCP:
		if (likely(pskb_may_pull(skb, nhoff + sizeof(struct tcphdr)))) {
			struct tcphdr *th = (struct tcphdr *)
					(skb_network_header(skb) + nhoff);

			diff = get_csum_diff(ip6h, p);
			inet_proto_csum_replace_by_diff(&th->check, skb,
							diff, true);
		}
		break;
	case NEXTHDR_UDP:
		if (likely(pskb_may_pull(skb, nhoff + sizeof(struct udphdr)))) {
			struct udphdr *uh = (struct udphdr *)
					(skb_network_header(skb) + nhoff);

			if (uh->check || skb->ip_summed == CHECKSUM_PARTIAL) {
				diff = get_csum_diff(ip6h, p);
				inet_proto_csum_replace_by_diff(&uh->check, skb,
								diff, true);
				if (!uh->check)
					uh->check = CSUM_MANGLED_0;
			}
		}
		break;
	case NEXTHDR_ICMP:
		if (likely(pskb_may_pull(skb,
					 nhoff + sizeof(struct icmp6hdr)))) {
			struct icmp6hdr *ih = (struct icmp6hdr *)
					(skb_network_header(skb) + nhoff);

			diff = get_csum_diff(ip6h, p);
			inet_proto_csum_replace_by_diff(&ih->icmp6_cksum, skb,
							diff, true);
		}
		break;
	}
}