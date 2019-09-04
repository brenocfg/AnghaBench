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
struct fib6_info {int /*<<< orphan*/  rt6i_pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_hold_safe (int /*<<< orphan*/ *,struct rt6_info**,int) ; 
 struct rt6_info** this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rt6_info *rt6_get_pcpu_route(struct fib6_info *rt)
{
	struct rt6_info *pcpu_rt, **p;

	p = this_cpu_ptr(rt->rt6i_pcpu);
	pcpu_rt = *p;

	if (pcpu_rt)
		ip6_hold_safe(NULL, &pcpu_rt, false);

	return pcpu_rt;
}