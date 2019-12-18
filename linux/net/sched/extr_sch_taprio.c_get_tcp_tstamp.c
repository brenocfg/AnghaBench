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
struct taprio_sched {int /*<<< orphan*/  tk_offset; } ;
struct sk_buff {int /*<<< orphan*/  skb_mstamp_ns; } ;
struct ipv6hdr {int version; scalar_t__ nexthdr; } ;
struct iphdr {int ihl; scalar_t__ protocol; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  _ipv6h ;

/* Variables and functions */
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  ktime_mono_to_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct ipv6hdr*) ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static ktime_t get_tcp_tstamp(struct taprio_sched *q, struct sk_buff *skb)
{
	unsigned int offset = skb_network_offset(skb);
	const struct ipv6hdr *ipv6h;
	const struct iphdr *iph;
	struct ipv6hdr _ipv6h;

	ipv6h = skb_header_pointer(skb, offset, sizeof(_ipv6h), &_ipv6h);
	if (!ipv6h)
		return 0;

	if (ipv6h->version == 4) {
		iph = (struct iphdr *)ipv6h;
		offset += iph->ihl * 4;

		/* special-case 6in4 tunnelling, as that is a common way to get
		 * v6 connectivity in the home
		 */
		if (iph->protocol == IPPROTO_IPV6) {
			ipv6h = skb_header_pointer(skb, offset,
						   sizeof(_ipv6h), &_ipv6h);

			if (!ipv6h || ipv6h->nexthdr != IPPROTO_TCP)
				return 0;
		} else if (iph->protocol != IPPROTO_TCP) {
			return 0;
		}
	} else if (ipv6h->version == 6 && ipv6h->nexthdr != IPPROTO_TCP) {
		return 0;
	}

	return ktime_mono_to_any(skb->skb_mstamp_ns, q->tk_offset);
}