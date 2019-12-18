#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int dummy; } ;
struct ipv6hdr {int version; int hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  payload_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ cfg_payload_len ; 
 TYPE_1__ daddr6 ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ipv6hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_header_ipv6(void *p)
{
	struct ipv6hdr *ip6h = p;

	memset(ip6h, 0, sizeof(*ip6h));

	ip6h->version		= 6;
	ip6h->payload_len	= htons(sizeof(struct udphdr) + cfg_payload_len);
	ip6h->nexthdr		= IPPROTO_UDP;
	ip6h->hop_limit		= 64;

	ip6h->saddr             = daddr6.sin6_addr;
	ip6h->daddr		= daddr6.sin6_addr;

	/* kernel does not write saddr in case of ipv6 */

	return sizeof(*ip6h);
}