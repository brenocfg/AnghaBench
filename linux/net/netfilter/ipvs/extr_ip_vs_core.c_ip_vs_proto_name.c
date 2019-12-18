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

/* Variables and functions */
#define  IPPROTO_ICMP 133 
#define  IPPROTO_ICMPV6 132 
#define  IPPROTO_IP 131 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

const char *ip_vs_proto_name(unsigned int proto)
{
	static char buf[20];

	switch (proto) {
	case IPPROTO_IP:
		return "IP";
	case IPPROTO_UDP:
		return "UDP";
	case IPPROTO_TCP:
		return "TCP";
	case IPPROTO_SCTP:
		return "SCTP";
	case IPPROTO_ICMP:
		return "ICMP";
#ifdef CONFIG_IP_VS_IPV6
	case IPPROTO_ICMPV6:
		return "ICMPv6";
#endif
	default:
		sprintf(buf, "IP_%u", proto);
		return buf;
	}
}