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
struct ipv6_sr_hdr {int segments_left; struct in6_addr* segments; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void advance_nextseg(struct ipv6_sr_hdr *srh, struct in6_addr *daddr)
{
	struct in6_addr *addr;

	srh->segments_left--;
	addr = srh->segments + srh->segments_left;
	*daddr = *addr;
}