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
typedef  scalar_t__ u8 ;
typedef  struct tcphdr {scalar_t__ rst; } const tcphdr ;
struct sk_buff {int data; int len; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr (struct sk_buff*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ip6_checksum (struct sk_buff*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct tcphdr const* skb_header_pointer (struct sk_buff*,int,int,struct tcphdr const*) ; 

const struct tcphdr *nf_reject_ip6_tcphdr_get(struct sk_buff *oldskb,
					      struct tcphdr *otcph,
					      unsigned int *otcplen, int hook)
{
	const struct ipv6hdr *oip6h = ipv6_hdr(oldskb);
	u8 proto;
	__be16 frag_off;
	int tcphoff;

	proto = oip6h->nexthdr;
	tcphoff = ipv6_skip_exthdr(oldskb, ((u8 *)(oip6h + 1) - oldskb->data),
				   &proto, &frag_off);

	if ((tcphoff < 0) || (tcphoff > oldskb->len)) {
		pr_debug("Cannot get TCP header.\n");
		return NULL;
	}

	*otcplen = oldskb->len - tcphoff;

	/* IP header checks: fragment, too short. */
	if (proto != IPPROTO_TCP || *otcplen < sizeof(struct tcphdr)) {
		pr_debug("proto(%d) != IPPROTO_TCP or too short (len = %d)\n",
			 proto, *otcplen);
		return NULL;
	}

	otcph = skb_header_pointer(oldskb, tcphoff, sizeof(struct tcphdr),
				   otcph);
	if (otcph == NULL)
		return NULL;

	/* No RST for RST. */
	if (otcph->rst) {
		pr_debug("RST is set\n");
		return NULL;
	}

	/* Check checksum. */
	if (nf_ip6_checksum(oldskb, hook, tcphoff, IPPROTO_TCP)) {
		pr_debug("TCP checksum is invalid\n");
		return NULL;
	}

	return otcph;
}