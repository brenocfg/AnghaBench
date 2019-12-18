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
typedef  int u32 ;
struct fib6_nh {scalar_t__ fib_nh_gw_family; TYPE_1__* fib_nh_dev; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int IPV6_DECODE_PREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV6_EXTRACT_PREF (int) ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int RT6_NUD_FAIL_HARD ; 
 int RTF_NONEXTHOP ; 
 int rt6_check_neigh (struct fib6_nh const*) ; 

__attribute__((used)) static int rt6_score_route(const struct fib6_nh *nh, u32 fib6_flags, int oif,
			   int strict)
{
	int m = 0;

	if (!oif || nh->fib_nh_dev->ifindex == oif)
		m = 2;

	if (!m && (strict & RT6_LOOKUP_F_IFACE))
		return RT6_NUD_FAIL_HARD;
#ifdef CONFIG_IPV6_ROUTER_PREF
	m |= IPV6_DECODE_PREF(IPV6_EXTRACT_PREF(fib6_flags)) << 2;
#endif
	if ((strict & RT6_LOOKUP_F_REACHABLE) &&
	    !(fib6_flags & RTF_NONEXTHOP) && nh->fib_nh_gw_family) {
		int n = rt6_check_neigh(nh);
		if (n < 0)
			return n;
	}
	return m;
}