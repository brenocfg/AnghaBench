#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * u6_addr32; } ;
struct TYPE_8__ {TYPE_3__ in6_u; } ;
struct TYPE_5__ {int /*<<< orphan*/ * u6_addr32; } ;
struct TYPE_6__ {TYPE_1__ in6_u; } ;
struct ipv6hdr {int hop_limit; TYPE_4__ daddr; TYPE_2__ saddr; } ;
struct icmp6hdr {int icmp6_type; int icmp6_cksum; } ;
struct eth_hdr {int dummy; } ;
typedef  int __u64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int XDP_DROP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int swap_mac_and_send (void*,void*) ; 

__attribute__((used)) static __attribute__ ((noinline))
int send_icmp6_reply(void *data, void *data_end)
{
	struct icmp6hdr *icmp_hdr;
	struct ipv6hdr *ip6h;
	__be32 tmp_addr[4];
	__u64 off = 0;

	if (data + sizeof(struct eth_hdr)
	     + sizeof(struct ipv6hdr) + sizeof(struct icmp6hdr) > data_end)
		return XDP_DROP;
	off += sizeof(struct eth_hdr);
	ip6h = data + off;
	off += sizeof(struct ipv6hdr);
	icmp_hdr = data + off;
	icmp_hdr->icmp6_type = 129;
	icmp_hdr->icmp6_cksum -= 0x0001;
	ip6h->hop_limit = 4;
	memcpy(tmp_addr, ip6h->saddr.in6_u.u6_addr32, 16);
	memcpy(ip6h->saddr.in6_u.u6_addr32, ip6h->daddr.in6_u.u6_addr32, 16);
	memcpy(ip6h->daddr.in6_u.u6_addr32, tmp_addr, 16);
	return swap_mac_and_send(data, data_end);
}