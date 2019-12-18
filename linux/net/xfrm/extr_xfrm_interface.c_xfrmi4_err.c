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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct xfrm_if {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mark; scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct iphdr {int protocol; int ihl; int /*<<< orphan*/  daddr; } ;
struct ip_esp_hdr {int /*<<< orphan*/  spi; } ;
struct ip_comp_hdr {int /*<<< orphan*/  cpi; } ;
struct ip_auth_hdr {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int type; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  ICMP_DEST_UNREACH 132 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
#define  ICMP_REDIRECT 131 
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_1__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_redirect (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipv4_update_pmtu (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct xfrm_if* xfrmi_lookup (struct net*,struct xfrm_state*) ; 

__attribute__((used)) static int xfrmi4_err(struct sk_buff *skb, u32 info)
{
	const struct iphdr *iph = (const struct iphdr *)skb->data;
	struct net *net = dev_net(skb->dev);
	int protocol = iph->protocol;
	struct ip_comp_hdr *ipch;
	struct ip_esp_hdr *esph;
	struct ip_auth_hdr *ah ;
	struct xfrm_state *x;
	struct xfrm_if *xi;
	__be32 spi;

	switch (protocol) {
	case IPPROTO_ESP:
		esph = (struct ip_esp_hdr *)(skb->data+(iph->ihl<<2));
		spi = esph->spi;
		break;
	case IPPROTO_AH:
		ah = (struct ip_auth_hdr *)(skb->data+(iph->ihl<<2));
		spi = ah->spi;
		break;
	case IPPROTO_COMP:
		ipch = (struct ip_comp_hdr *)(skb->data+(iph->ihl<<2));
		spi = htonl(ntohs(ipch->cpi));
		break;
	default:
		return 0;
	}

	switch (icmp_hdr(skb)->type) {
	case ICMP_DEST_UNREACH:
		if (icmp_hdr(skb)->code != ICMP_FRAG_NEEDED)
			return 0;
	case ICMP_REDIRECT:
		break;
	default:
		return 0;
	}

	x = xfrm_state_lookup(net, skb->mark, (const xfrm_address_t *)&iph->daddr,
			      spi, protocol, AF_INET);
	if (!x)
		return 0;

	xi = xfrmi_lookup(net, x);
	if (!xi) {
		xfrm_state_put(x);
		return -1;
	}

	if (icmp_hdr(skb)->type == ICMP_DEST_UNREACH)
		ipv4_update_pmtu(skb, net, info, 0, protocol);
	else
		ipv4_redirect(skb, net, 0, protocol);
	xfrm_state_put(x);

	return 0;
}