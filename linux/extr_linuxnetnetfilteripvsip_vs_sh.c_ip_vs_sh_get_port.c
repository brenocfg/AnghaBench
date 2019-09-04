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
struct sk_buff {int dummy; } ;
struct ip_vs_iphdr {int protocol; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  ip_vs_iph_inverse (struct ip_vs_iphdr*) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static inline __be16
ip_vs_sh_get_port(const struct sk_buff *skb, struct ip_vs_iphdr *iph)
{
	__be16 _ports[2], *ports;

	/* At this point we know that we have a valid packet of some kind.
	 * Because ICMP packets are only guaranteed to have the first 8
	 * bytes, let's just grab the ports.  Fortunately they're in the
	 * same position for all three of the protocols we care about.
	 */
	switch (iph->protocol) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
	case IPPROTO_SCTP:
		ports = skb_header_pointer(skb, iph->len, sizeof(_ports),
					   &_ports);
		if (unlikely(!ports))
			return 0;

		if (likely(!ip_vs_iph_inverse(iph)))
			return ports[0];
		else
			return ports[1];
	default:
		return 0;
	}
}