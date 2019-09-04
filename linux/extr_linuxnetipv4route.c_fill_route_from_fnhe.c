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
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct rtable {int rt_uses_gateway; scalar_t__ rt_gateway; int /*<<< orphan*/  rt_flags; TYPE_1__ dst; int /*<<< orphan*/  rt_mtu_locked; int /*<<< orphan*/  rt_pmtu; } ;
struct fib_nh_exception {scalar_t__ fnhe_gw; int /*<<< orphan*/  fnhe_expires; int /*<<< orphan*/  fnhe_mtu_locked; int /*<<< orphan*/  fnhe_pmtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTCF_REDIRECTED ; 

__attribute__((used)) static void fill_route_from_fnhe(struct rtable *rt, struct fib_nh_exception *fnhe)
{
	rt->rt_pmtu = fnhe->fnhe_pmtu;
	rt->rt_mtu_locked = fnhe->fnhe_mtu_locked;
	rt->dst.expires = fnhe->fnhe_expires;

	if (fnhe->fnhe_gw) {
		rt->rt_flags |= RTCF_REDIRECTED;
		rt->rt_gateway = fnhe->fnhe_gw;
		rt->rt_uses_gateway = 1;
	}
}