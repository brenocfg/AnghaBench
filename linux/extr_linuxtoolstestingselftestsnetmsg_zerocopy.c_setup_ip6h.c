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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct ipv6hdr {int version; int hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_EGP ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 int /*<<< orphan*/  cfg_src_addr ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ipv6hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_ip6h(struct ipv6hdr *ip6h, uint16_t payload_len)
{
	struct sockaddr_in6 *daddr = (void *) &cfg_dst_addr;
	struct sockaddr_in6 *saddr = (void *) &cfg_src_addr;

	memset(ip6h, 0, sizeof(*ip6h));

	ip6h->version		= 6;
	ip6h->payload_len	= htons(payload_len);
	ip6h->nexthdr		= IPPROTO_EGP;
	ip6h->hop_limit		= 2;
	ip6h->saddr		= saddr->sin6_addr;
	ip6h->daddr		= daddr->sin6_addr;

	return sizeof(*ip6h);
}