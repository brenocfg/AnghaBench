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
struct TYPE_2__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_info {int /*<<< orphan*/  rt6i_pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct rt6_info*) ; 
 struct rt6_info* cmpxchg (struct rt6_info**,int /*<<< orphan*/ *,struct rt6_info*) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 struct rt6_info* ip6_rt_pcpu_alloc (struct fib6_info*) ; 
 struct rt6_info** this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rt6_info *rt6_make_pcpu_route(struct net *net,
					    struct fib6_info *rt)
{
	struct rt6_info *pcpu_rt, *prev, **p;

	pcpu_rt = ip6_rt_pcpu_alloc(rt);
	if (!pcpu_rt) {
		dst_hold(&net->ipv6.ip6_null_entry->dst);
		return net->ipv6.ip6_null_entry;
	}

	dst_hold(&pcpu_rt->dst);
	p = this_cpu_ptr(rt->rt6i_pcpu);
	prev = cmpxchg(p, NULL, pcpu_rt);
	BUG_ON(prev);

	return pcpu_rt;
}