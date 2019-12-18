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
typedef  scalar_t__ u32 ;
struct dst_entry {int /*<<< orphan*/  dev; scalar_t__ expires; } ;
struct rtable {scalar_t__ rt_pmtu; struct dst_entry dst; } ;
struct flowi4 {int /*<<< orphan*/  daddr; } ;
struct fib_result {int dummy; } ;
struct fib_nh_common {int dummy; } ;

/* Variables and functions */
 struct fib_nh_common* FIB_RES_NHC (struct fib_result) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ fib_lookup (int /*<<< orphan*/ ,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_mtu_locked (struct dst_entry*) ; 
 scalar_t__ ip_rt_min_pmtu ; 
 int ip_rt_mtu_expires ; 
 scalar_t__ ipv4_mtu (struct dst_entry*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  update_or_create_fnhe (struct fib_nh_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static void __ip_rt_update_pmtu(struct rtable *rt, struct flowi4 *fl4, u32 mtu)
{
	struct dst_entry *dst = &rt->dst;
	u32 old_mtu = ipv4_mtu(dst);
	struct fib_result res;
	bool lock = false;

	if (ip_mtu_locked(dst))
		return;

	if (old_mtu < mtu)
		return;

	if (mtu < ip_rt_min_pmtu) {
		lock = true;
		mtu = min(old_mtu, ip_rt_min_pmtu);
	}

	if (rt->rt_pmtu == mtu && !lock &&
	    time_before(jiffies, dst->expires - ip_rt_mtu_expires / 2))
		return;

	rcu_read_lock();
	if (fib_lookup(dev_net(dst->dev), fl4, &res, 0) == 0) {
		struct fib_nh_common *nhc = FIB_RES_NHC(res);

		update_or_create_fnhe(nhc, fl4->daddr, 0, mtu, lock,
				      jiffies + ip_rt_mtu_expires);
	}
	rcu_read_unlock();
}