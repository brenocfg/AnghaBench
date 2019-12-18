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
struct fib6_nh_del_cached_rt_arg {struct fib6_info* f6i; struct fib6_config* cfg; } ;
struct fib6_info {int /*<<< orphan*/  nh; } ;
struct fib6_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_nh_del_cached_rt ; 
 int nexthop_for_each_fib6_nh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib6_nh_del_cached_rt_arg*) ; 

__attribute__((used)) static int ip6_del_cached_rt_nh(struct fib6_config *cfg, struct fib6_info *f6i)
{
	struct fib6_nh_del_cached_rt_arg arg = {
		.cfg = cfg,
		.f6i = f6i
	};

	return nexthop_for_each_fib6_nh(f6i->nh, fib6_nh_del_cached_rt, &arg);
}