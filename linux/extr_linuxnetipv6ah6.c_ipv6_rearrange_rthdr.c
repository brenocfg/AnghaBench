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
struct rt0_hdr {struct in6_addr* addr; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {struct in6_addr daddr; } ;
struct ipv6_rt_hdr {int segments_left; int hdrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (struct in6_addr*,struct in6_addr*,int) ; 

__attribute__((used)) static void ipv6_rearrange_rthdr(struct ipv6hdr *iph, struct ipv6_rt_hdr *rthdr)
{
	int segments, segments_left;
	struct in6_addr *addrs;
	struct in6_addr final_addr;

	segments_left = rthdr->segments_left;
	if (segments_left == 0)
		return;
	rthdr->segments_left = 0;

	/* The value of rthdr->hdrlen has been verified either by the system
	 * call if it is locally generated, or by ipv6_rthdr_rcv() for incoming
	 * packets.  So we can assume that it is even and that segments is
	 * greater than or equal to segments_left.
	 *
	 * For the same reason we can assume that this option is of type 0.
	 */
	segments = rthdr->hdrlen >> 1;

	addrs = ((struct rt0_hdr *)rthdr)->addr;
	final_addr = addrs[segments - 1];

	addrs += segments - segments_left;
	memmove(addrs + 1, addrs, (segments_left - 1) * sizeof(*addrs));

	addrs[0] = iph->daddr;
	iph->daddr = final_addr;
}