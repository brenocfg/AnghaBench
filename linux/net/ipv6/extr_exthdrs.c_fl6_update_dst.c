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
struct rt0_hdr {struct in6_addr* addr; } ;
struct ipv6_txoptions {TYPE_1__* srcrt; } ;
struct ipv6_sr_hdr {size_t segments_left; struct in6_addr* segments; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {struct in6_addr daddr; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  IPV6_SRCRT_STRICT 131 
#define  IPV6_SRCRT_TYPE_0 130 
#define  IPV6_SRCRT_TYPE_2 129 
#define  IPV6_SRCRT_TYPE_4 128 

struct in6_addr *fl6_update_dst(struct flowi6 *fl6,
				const struct ipv6_txoptions *opt,
				struct in6_addr *orig)
{
	if (!opt || !opt->srcrt)
		return NULL;

	*orig = fl6->daddr;

	switch (opt->srcrt->type) {
	case IPV6_SRCRT_TYPE_0:
	case IPV6_SRCRT_STRICT:
	case IPV6_SRCRT_TYPE_2:
		fl6->daddr = *((struct rt0_hdr *)opt->srcrt)->addr;
		break;
	case IPV6_SRCRT_TYPE_4:
	{
		struct ipv6_sr_hdr *srh = (struct ipv6_sr_hdr *)opt->srcrt;

		fl6->daddr = srh->segments[srh->segments_left];
		break;
	}
	default:
		return NULL;
	}

	return orig;
}