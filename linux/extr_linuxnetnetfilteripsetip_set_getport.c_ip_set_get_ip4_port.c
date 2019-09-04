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
struct sk_buff {int dummy; } ;
struct iphdr {int protocol; int /*<<< orphan*/  frag_off; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  IPPROTO_ICMP 132 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int IP_OFFSET ; 
 int get_port (struct sk_buff const*,int,unsigned int,int,int /*<<< orphan*/ *,int*) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 unsigned int ip_hdrlen (struct sk_buff const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 unsigned int skb_network_offset (struct sk_buff const*) ; 

bool
ip_set_get_ip4_port(const struct sk_buff *skb, bool src,
		    __be16 *port, u8 *proto)
{
	const struct iphdr *iph = ip_hdr(skb);
	unsigned int protooff = skb_network_offset(skb) + ip_hdrlen(skb);
	int protocol = iph->protocol;

	/* See comments at tcp_match in ip_tables.c */
	if (protocol <= 0)
		return false;

	if (ntohs(iph->frag_off) & IP_OFFSET)
		switch (protocol) {
		case IPPROTO_TCP:
		case IPPROTO_SCTP:
		case IPPROTO_UDP:
		case IPPROTO_UDPLITE:
		case IPPROTO_ICMP:
			/* Port info not available for fragment offset > 0 */
			return false;
		default:
			/* Other protocols doesn't have ports,
			 * so we can match fragments.
			 */
			*proto = protocol;
			return true;
		}

	return get_port(skb, protocol, protooff, src, port, proto);
}