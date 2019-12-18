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
struct rt6_info {int /*<<< orphan*/  rt6i_gateway; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {scalar_t__ flowi6_oif; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct fib6_result {struct fib6_nh* nh; } ;
struct fib6_nh {int fib_nh_flags; int /*<<< orphan*/  fib_nh_gw6; TYPE_1__* fib_nh_dev; int /*<<< orphan*/  fib_nh_gw_family; } ;
struct TYPE_2__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int RTNH_F_DEAD ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr const*,int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_find_cached_rt (struct fib6_result const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ip6_redirect_nh_match(const struct fib6_result *res,
				  struct flowi6 *fl6,
				  const struct in6_addr *gw,
				  struct rt6_info **ret)
{
	const struct fib6_nh *nh = res->nh;

	if (nh->fib_nh_flags & RTNH_F_DEAD || !nh->fib_nh_gw_family ||
	    fl6->flowi6_oif != nh->fib_nh_dev->ifindex)
		return false;

	/* rt_cache's gateway might be different from its 'parent'
	 * in the case of an ip redirect.
	 * So we keep searching in the exception table if the gateway
	 * is different.
	 */
	if (!ipv6_addr_equal(gw, &nh->fib_nh_gw6)) {
		struct rt6_info *rt_cache;

		rt_cache = rt6_find_cached_rt(res, &fl6->daddr, &fl6->saddr);
		if (rt_cache &&
		    ipv6_addr_equal(gw, &rt_cache->rt6i_gateway)) {
			*ret = rt_cache;
			return true;
		}
		return false;
	}
	return true;
}