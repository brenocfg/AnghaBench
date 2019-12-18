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
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct icmphdr {int dummy; } ;
struct icmp6hdr {int dummy; } ;
struct eth_hdr {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */

__attribute__((used)) static inline __u64 calc_offset(bool is_ipv6, bool is_icmp)
{
	__u64 off = sizeof(struct eth_hdr);
	if (is_ipv6) {
		off += sizeof(struct ipv6hdr);
		if (is_icmp)
			off += sizeof(struct icmp6hdr) + sizeof(struct ipv6hdr);
	} else {
		off += sizeof(struct iphdr);
		if (is_icmp)
			off += sizeof(struct icmphdr) + sizeof(struct iphdr);
	}
	return off;
}