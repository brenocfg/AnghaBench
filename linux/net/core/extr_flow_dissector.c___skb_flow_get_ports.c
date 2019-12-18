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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {void* data; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * __skb_header_pointer (struct sk_buff const*,int,int,void*,int,int /*<<< orphan*/ *) ; 
 int proto_ports_offset (int /*<<< orphan*/ ) ; 
 int skb_headlen (struct sk_buff const*) ; 

__be32 __skb_flow_get_ports(const struct sk_buff *skb, int thoff, u8 ip_proto,
			    void *data, int hlen)
{
	int poff = proto_ports_offset(ip_proto);

	if (!data) {
		data = skb->data;
		hlen = skb_headlen(skb);
	}

	if (poff >= 0) {
		__be32 *ports, _ports;

		ports = __skb_header_pointer(skb, thoff + poff,
					     sizeof(_ports), data, hlen, &_ports);
		if (ports)
			return *ports;
	}

	return 0;
}