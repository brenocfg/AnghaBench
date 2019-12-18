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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct ipv6hdr {int version; int hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ipv6_set_dsfield (struct ipv6hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void build_ipv6_header(void *header, uint8_t proto,
			      struct sockaddr_in6 *src,
			      struct sockaddr_in6 *dst,
			      int payload_len, uint8_t dsfield)
{
	struct ipv6hdr *ip6h = header;

	ip6h->version = 6;
	ip6h->payload_len = htons(payload_len);
	ip6h->nexthdr = proto;
	ip6h->hop_limit = 8;
	ipv6_set_dsfield(ip6h, dsfield);

	memcpy(&ip6h->saddr, &src->sin6_addr, sizeof(ip6h->saddr));
	memcpy(&ip6h->daddr, &dst->sin6_addr, sizeof(ip6h->daddr));
}