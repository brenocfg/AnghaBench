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
struct rt6_info {int dummy; } ;
struct fib6_result {struct fib6_nh* nh; struct fib6_info* f6i; } ;
struct fib6_nh {int dummy; } ;
struct fib6_info {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_src; int /*<<< orphan*/  fc_dst; } ;

/* Variables and functions */
 int __ip6_del_cached_rt (struct rt6_info*,struct fib6_config*) ; 
 struct rt6_info* rt6_find_cached_rt (struct fib6_result*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip6_del_cached_rt(struct fib6_config *cfg, struct fib6_info *rt,
			     struct fib6_nh *nh)
{
	struct fib6_result res = {
		.f6i = rt,
		.nh = nh,
	};
	struct rt6_info *rt_cache;

	rt_cache = rt6_find_cached_rt(&res, &cfg->fc_dst, &cfg->fc_src);
	if (rt_cache)
		return __ip6_del_cached_rt(rt_cache, cfg);

	return 0;
}