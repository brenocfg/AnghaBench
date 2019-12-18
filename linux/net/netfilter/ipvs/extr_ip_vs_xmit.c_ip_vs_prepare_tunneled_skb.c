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
struct sk_buff {scalar_t__ sk; } ;
struct ipv6hdr {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  payload_len; } ;
struct iphdr {int frag_off; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  ttl; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u32 ;
typedef  int __be16 ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INET_ECN_encapsulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  ip_vs_drop_early_demux_sk (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_get_dsfield (struct iphdr*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *
ip_vs_prepare_tunneled_skb(struct sk_buff *skb, int skb_af,
			   unsigned int max_headroom, __u8 *next_protocol,
			   __u32 *payload_len, __u8 *dsfield, __u8 *ttl,
			   __be16 *df)
{
	struct sk_buff *new_skb = NULL;
	struct iphdr *old_iph = NULL;
	__u8 old_dsfield;
#ifdef CONFIG_IP_VS_IPV6
	struct ipv6hdr *old_ipv6h = NULL;
#endif

	ip_vs_drop_early_demux_sk(skb);

	if (skb_headroom(skb) < max_headroom || skb_cloned(skb)) {
		new_skb = skb_realloc_headroom(skb, max_headroom);
		if (!new_skb)
			goto error;
		if (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	}

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		old_ipv6h = ipv6_hdr(skb);
		*next_protocol = IPPROTO_IPV6;
		if (payload_len)
			*payload_len =
				ntohs(old_ipv6h->payload_len) +
				sizeof(*old_ipv6h);
		old_dsfield = ipv6_get_dsfield(old_ipv6h);
		*ttl = old_ipv6h->hop_limit;
		if (df)
			*df = 0;
	} else
#endif
	{
		old_iph = ip_hdr(skb);
		/* Copy DF, reset fragment offset and MF */
		if (df)
			*df = (old_iph->frag_off & htons(IP_DF));
		*next_protocol = IPPROTO_IPIP;

		/* fix old IP header checksum */
		ip_send_check(old_iph);
		old_dsfield = ipv4_get_dsfield(old_iph);
		*ttl = old_iph->ttl;
		if (payload_len)
			*payload_len = ntohs(old_iph->tot_len);
	}

	/* Implement full-functionality option for ECN encapsulation */
	*dsfield = INET_ECN_encapsulate(old_dsfield, old_dsfield);

	return skb;
error:
	kfree_skb(skb);
	return ERR_PTR(-ENOMEM);
}