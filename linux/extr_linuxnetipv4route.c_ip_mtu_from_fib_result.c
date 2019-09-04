#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct fib_result {size_t nh_sel; struct fib_info* fi; } ;
struct fib_nh_exception {scalar_t__ fnhe_pmtu; int /*<<< orphan*/  fnhe_expires; } ;
struct fib_nh {int /*<<< orphan*/  nh_lwtstate; struct net_device* nh_dev; } ;
struct fib_info {scalar_t__ fib_mtu; TYPE_2__* fib_metrics; struct fib_nh* fib_nh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ sysctl_ip_fwd_use_pmtu; } ;
struct TYPE_6__ {TYPE_1__ ipv4; } ;
struct TYPE_5__ {int* metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_MAX_MTU ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int RTAX_LOCK ; 
 int RTAX_MTU ; 
 TYPE_3__* dev_net (struct net_device*) ; 
 struct fib_nh_exception* find_exception (struct fib_nh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 scalar_t__ lwtunnel_headroom (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 ip_mtu_from_fib_result(struct fib_result *res, __be32 daddr)
{
	struct fib_info *fi = res->fi;
	struct fib_nh *nh = &fi->fib_nh[res->nh_sel];
	struct net_device *dev = nh->nh_dev;
	u32 mtu = 0;

	if (dev_net(dev)->ipv4.sysctl_ip_fwd_use_pmtu ||
	    fi->fib_metrics->metrics[RTAX_LOCK - 1] & (1 << RTAX_MTU))
		mtu = fi->fib_mtu;

	if (likely(!mtu)) {
		struct fib_nh_exception *fnhe;

		fnhe = find_exception(nh, daddr);
		if (fnhe && !time_after_eq(jiffies, fnhe->fnhe_expires))
			mtu = fnhe->fnhe_pmtu;
	}

	if (likely(!mtu))
		mtu = min(READ_ONCE(dev->mtu), IP_MAX_MTU);

	return mtu - lwtunnel_headroom(nh->nh_lwtstate, mtu);
}