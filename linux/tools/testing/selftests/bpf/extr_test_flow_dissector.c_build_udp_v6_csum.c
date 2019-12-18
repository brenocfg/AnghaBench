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
typedef  int /*<<< orphan*/  uint16_t ;
struct udphdr {int dummy; } ;
struct ipv6hdr {scalar_t__ payload_len; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned long add_csum_hword (void*,int) ; 
 int /*<<< orphan*/  build_ip_csum (void*,int,unsigned long) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t build_udp_v6_csum(const struct ipv6hdr *ip6h,
				  const struct udphdr *udph,
				  int num_words)
{
	unsigned long pseudo_sum;
	int num_u16 = sizeof(ip6h->saddr);	/* halfwords: twice byte len */

	pseudo_sum = add_csum_hword((void *) &ip6h->saddr, num_u16);
	pseudo_sum += htons(ip6h->nexthdr);
	pseudo_sum += ip6h->payload_len;
	return build_ip_csum((void *) udph, num_words, pseudo_sum);
}