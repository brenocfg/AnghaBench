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
struct sk_buff {scalar_t__ mac_len; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  nexthdr; } ;
struct ipv6_sr_hdr {int hdrlen; size_t first_segment; int /*<<< orphan*/ * segments; int /*<<< orphan*/  nexthdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXTHDR_ROUTING ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct ipv6_sr_hdr*,struct ipv6_sr_hdr*,int) ; 
 int /*<<< orphan*/  memmove (struct ipv6hdr*,struct ipv6hdr*,int) ; 
 int seg6_push_hmac (struct net*,int /*<<< orphan*/ *,struct ipv6_sr_hdr*) ; 
 int skb_cow_head (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_rebuild (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,struct ipv6hdr*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 scalar_t__ sr_has_hmac (struct ipv6_sr_hdr*) ; 
 scalar_t__ unlikely (int) ; 

int seg6_do_srh_inline(struct sk_buff *skb, struct ipv6_sr_hdr *osrh)
{
	struct ipv6hdr *hdr, *oldhdr;
	struct ipv6_sr_hdr *isrh;
	int hdrlen, err;

	hdrlen = (osrh->hdrlen + 1) << 3;

	err = skb_cow_head(skb, hdrlen + skb->mac_len);
	if (unlikely(err))
		return err;

	oldhdr = ipv6_hdr(skb);

	skb_pull(skb, sizeof(struct ipv6hdr));
	skb_postpull_rcsum(skb, skb_network_header(skb),
			   sizeof(struct ipv6hdr));

	skb_push(skb, sizeof(struct ipv6hdr) + hdrlen);
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);

	hdr = ipv6_hdr(skb);

	memmove(hdr, oldhdr, sizeof(*hdr));

	isrh = (void *)hdr + sizeof(*hdr);
	memcpy(isrh, osrh, hdrlen);

	isrh->nexthdr = hdr->nexthdr;
	hdr->nexthdr = NEXTHDR_ROUTING;

	isrh->segments[0] = hdr->daddr;
	hdr->daddr = isrh->segments[isrh->first_segment];

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (sr_has_hmac(isrh)) {
		struct net *net = dev_net(skb_dst(skb)->dev);

		err = seg6_push_hmac(net, &hdr->saddr, isrh);
		if (unlikely(err))
			return err;
	}
#endif

	skb_postpush_rcsum(skb, hdr, sizeof(struct ipv6hdr) + hdrlen);

	return 0;
}