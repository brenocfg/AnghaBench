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
struct udphdr {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  get_ip_csum (void const*,unsigned long,unsigned long) ; 
 unsigned long htons (int /*<<< orphan*/ ) ; 
 int ntohs (scalar_t__) ; 

__attribute__((used)) static uint16_t get_udp_csum(const struct udphdr *udph, int alen)
{
	unsigned long pseudo_sum, csum_len;
	const void *csum_start = udph;

	pseudo_sum = htons(IPPROTO_UDP);
	pseudo_sum += udph->len;

	/* checksum ip(v6) addresses + udp header + payload */
	csum_start -= alen * 2;
	csum_len = ntohs(udph->len) + alen * 2;

	return get_ip_csum(csum_start, csum_len >> 1, pseudo_sum);
}