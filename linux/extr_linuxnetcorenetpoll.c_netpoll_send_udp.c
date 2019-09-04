#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int source; int dest; int len; scalar_t__ check; } ;
struct sk_buff {int protocol; TYPE_3__* dev; } ;
struct TYPE_5__ {int ip; int /*<<< orphan*/  in6; } ;
struct TYPE_4__ {int ip; int /*<<< orphan*/  in6; } ;
struct netpoll {int local_port; int remote_port; TYPE_3__* dev; int /*<<< orphan*/  remote_mac; TYPE_2__ remote_ip; TYPE_1__ local_ip; scalar_t__ ipv6; } ;
struct ipv6hdr {int payload_len; int hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; void* nexthdr; scalar_t__* flow_lbl; } ;
struct iphdr {unsigned char tot_len; int id; int ttl; unsigned char saddr; unsigned char daddr; int /*<<< orphan*/  ihl; scalar_t__ check; void* protocol; scalar_t__ frag_off; scalar_t__ tos; } ;
struct ethhdr {int h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; scalar_t__ needed_tailroom; } ;

/* Variables and functions */
 void* CSUM_MANGLED_0 ; 
 int ETH_HLEN ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 void* IPPROTO_UDP ; 
 int LL_RESERVED_SPACE (TYPE_3__*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct udphdr*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tcpudp_magic (int,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* find_skb (struct netpoll*,scalar_t__,int) ; 
 int htons (int) ; 
 scalar_t__ ip_fast_csum (unsigned char*,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  netpoll_send_skb (struct netpoll*,struct sk_buff*) ; 
 int /*<<< orphan*/  put_unaligned (int,unsigned char*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,char const*,int) ; 
 struct ethhdr* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

void netpoll_send_udp(struct netpoll *np, const char *msg, int len)
{
	int total_len, ip_len, udp_len;
	struct sk_buff *skb;
	struct udphdr *udph;
	struct iphdr *iph;
	struct ethhdr *eth;
	static atomic_t ip_ident;
	struct ipv6hdr *ip6h;

	WARN_ON_ONCE(!irqs_disabled());

	udp_len = len + sizeof(*udph);
	if (np->ipv6)
		ip_len = udp_len + sizeof(*ip6h);
	else
		ip_len = udp_len + sizeof(*iph);

	total_len = ip_len + LL_RESERVED_SPACE(np->dev);

	skb = find_skb(np, total_len + np->dev->needed_tailroom,
		       total_len - len);
	if (!skb)
		return;

	skb_copy_to_linear_data(skb, msg, len);
	skb_put(skb, len);

	skb_push(skb, sizeof(*udph));
	skb_reset_transport_header(skb);
	udph = udp_hdr(skb);
	udph->source = htons(np->local_port);
	udph->dest = htons(np->remote_port);
	udph->len = htons(udp_len);

	if (np->ipv6) {
		udph->check = 0;
		udph->check = csum_ipv6_magic(&np->local_ip.in6,
					      &np->remote_ip.in6,
					      udp_len, IPPROTO_UDP,
					      csum_partial(udph, udp_len, 0));
		if (udph->check == 0)
			udph->check = CSUM_MANGLED_0;

		skb_push(skb, sizeof(*ip6h));
		skb_reset_network_header(skb);
		ip6h = ipv6_hdr(skb);

		/* ip6h->version = 6; ip6h->priority = 0; */
		put_unaligned(0x60, (unsigned char *)ip6h);
		ip6h->flow_lbl[0] = 0;
		ip6h->flow_lbl[1] = 0;
		ip6h->flow_lbl[2] = 0;

		ip6h->payload_len = htons(sizeof(struct udphdr) + len);
		ip6h->nexthdr = IPPROTO_UDP;
		ip6h->hop_limit = 32;
		ip6h->saddr = np->local_ip.in6;
		ip6h->daddr = np->remote_ip.in6;

		eth = skb_push(skb, ETH_HLEN);
		skb_reset_mac_header(skb);
		skb->protocol = eth->h_proto = htons(ETH_P_IPV6);
	} else {
		udph->check = 0;
		udph->check = csum_tcpudp_magic(np->local_ip.ip,
						np->remote_ip.ip,
						udp_len, IPPROTO_UDP,
						csum_partial(udph, udp_len, 0));
		if (udph->check == 0)
			udph->check = CSUM_MANGLED_0;

		skb_push(skb, sizeof(*iph));
		skb_reset_network_header(skb);
		iph = ip_hdr(skb);

		/* iph->version = 4; iph->ihl = 5; */
		put_unaligned(0x45, (unsigned char *)iph);
		iph->tos      = 0;
		put_unaligned(htons(ip_len), &(iph->tot_len));
		iph->id       = htons(atomic_inc_return(&ip_ident));
		iph->frag_off = 0;
		iph->ttl      = 64;
		iph->protocol = IPPROTO_UDP;
		iph->check    = 0;
		put_unaligned(np->local_ip.ip, &(iph->saddr));
		put_unaligned(np->remote_ip.ip, &(iph->daddr));
		iph->check    = ip_fast_csum((unsigned char *)iph, iph->ihl);

		eth = skb_push(skb, ETH_HLEN);
		skb_reset_mac_header(skb);
		skb->protocol = eth->h_proto = htons(ETH_P_IP);
	}

	ether_addr_copy(eth->h_source, np->dev->dev_addr);
	ether_addr_copy(eth->h_dest, np->remote_mac);

	skb->dev = np->dev;

	netpoll_send_skb(np, skb);
}