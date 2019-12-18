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
struct nh_info {int family; int /*<<< orphan*/  fib6_nh; int /*<<< orphan*/  fib_nh; } ;
struct nexthop {int /*<<< orphan*/  net; int /*<<< orphan*/  nh_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fib6_nh_release ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  fib_nh_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_stub ; 
 int /*<<< orphan*/  kfree (struct nh_info*) ; 
 struct nh_info* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nexthop_free_single(struct nexthop *nh)
{
	struct nh_info *nhi;

	nhi = rcu_dereference_raw(nh->nh_info);
	switch (nhi->family) {
	case AF_INET:
		fib_nh_release(nh->net, &nhi->fib_nh);
		break;
	case AF_INET6:
		ipv6_stub->fib6_nh_release(&nhi->fib6_nh);
		break;
	}
	kfree(nhi);
}