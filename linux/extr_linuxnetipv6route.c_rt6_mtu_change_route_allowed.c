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
struct rt6_info {int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int mtu6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int dst_mtu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rt6_mtu_change_route_allowed(struct inet6_dev *idev,
					 struct rt6_info *rt, int mtu)
{
	/* If the new MTU is lower than the route PMTU, this new MTU will be the
	 * lowest MTU in the path: always allow updating the route PMTU to
	 * reflect PMTU decreases.
	 *
	 * If the new MTU is higher, and the route PMTU is equal to the local
	 * MTU, this means the old MTU is the lowest in the path, so allow
	 * updating it: if other nodes now have lower MTUs, PMTU discovery will
	 * handle this.
	 */

	if (dst_mtu(&rt->dst) >= mtu)
		return true;

	if (dst_mtu(&rt->dst) == idev->cnf.mtu6)
		return true;

	return false;
}