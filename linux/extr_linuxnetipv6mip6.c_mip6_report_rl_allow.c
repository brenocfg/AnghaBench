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
struct in6_addr {int dummy; } ;
typedef  scalar_t__ ktime_t ;
struct TYPE_2__ {scalar_t__ stamp; int iif; int /*<<< orphan*/  lock; struct in6_addr dst; struct in6_addr src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_addr_equal (struct in6_addr*,struct in6_addr const*) ; 
 TYPE_1__ mip6_report_rl ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mip6_report_rl_allow(ktime_t stamp,
				       const struct in6_addr *dst,
				       const struct in6_addr *src, int iif)
{
	int allow = 0;

	spin_lock_bh(&mip6_report_rl.lock);
	if (mip6_report_rl.stamp != stamp ||
	    mip6_report_rl.iif != iif ||
	    !ipv6_addr_equal(&mip6_report_rl.src, src) ||
	    !ipv6_addr_equal(&mip6_report_rl.dst, dst)) {
		mip6_report_rl.stamp = stamp;
		mip6_report_rl.iif = iif;
		mip6_report_rl.src = *src;
		mip6_report_rl.dst = *dst;
		allow = 1;
	}
	spin_unlock_bh(&mip6_report_rl.lock);
	return allow;
}