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
struct xfrm_selector {int prefixlen_d; int prefixlen_s; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  proto; int /*<<< orphan*/  family; void* sport_mask; int /*<<< orphan*/  sport; void* dport_mask; int /*<<< orphan*/  dport; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  uli; struct in6_addr saddr; struct in6_addr daddr; } ;
struct TYPE_2__ {struct flowi6 ip6; } ;
struct flowi {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 void* htons (int) ; 
 int /*<<< orphan*/  xfrm_flowi_dport (struct flowi const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_flowi_sport (struct flowi const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__xfrm6_init_tempsel(struct xfrm_selector *sel, const struct flowi *fl)
{
	const struct flowi6 *fl6 = &fl->u.ip6;

	/* Initialize temporary selector matching only to current session. */
	*(struct in6_addr *)&sel->daddr = fl6->daddr;
	*(struct in6_addr *)&sel->saddr = fl6->saddr;
	sel->dport = xfrm_flowi_dport(fl, &fl6->uli);
	sel->dport_mask = htons(0xffff);
	sel->sport = xfrm_flowi_sport(fl, &fl6->uli);
	sel->sport_mask = htons(0xffff);
	sel->family = AF_INET6;
	sel->prefixlen_d = 128;
	sel->prefixlen_s = 128;
	sel->proto = fl6->flowi6_proto;
	sel->ifindex = fl6->flowi6_oif;
}