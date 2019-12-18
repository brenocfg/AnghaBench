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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct udphdr {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_src; } ;

/* Variables and functions */
 int CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int UDP_HLEN ; 
 int htons (int) ; 
 int payload_len ; 
 int raw_checksum (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ udp_payload ; 

__attribute__((used)) static uint16_t udp_checksum(struct ip *iphdr, struct udphdr *udphdr)
{
	uint32_t sum = 0;
	uint16_t res;

	sum = raw_checksum((uint8_t *)&iphdr->ip_src, 2 * sizeof(iphdr->ip_src),
				IPPROTO_UDP + (uint32_t)(UDP_HLEN + payload_len));
	sum = raw_checksum((uint8_t *)udphdr, UDP_HLEN, sum);
	sum = raw_checksum((uint8_t *)udp_payload, payload_len, sum);
	res = 0xffff & ~sum;
	if (res)
		return htons(res);
	else
		return CSUM_MANGLED_0;
}