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
struct rt6_info {int /*<<< orphan*/  from; struct inet6_dev* rt6i_idev; } ;
struct inet6_dev {int dummy; } ;
struct fib6_info {int dummy; } ;
struct dst_metrics {int /*<<< orphan*/  refcnt; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DST_METRICS_PTR (struct dst_entry*) ; 
 struct dst_metrics dst_default_metrics ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  kfree (struct dst_metrics*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt6_uncached_list_del (struct rt6_info*) ; 

__attribute__((used)) static void ip6_dst_destroy(struct dst_entry *dst)
{
	struct dst_metrics *p = (struct dst_metrics *)DST_METRICS_PTR(dst);
	struct rt6_info *rt = (struct rt6_info *)dst;
	struct fib6_info *from;
	struct inet6_dev *idev;

	if (p != &dst_default_metrics && refcount_dec_and_test(&p->refcnt))
		kfree(p);

	rt6_uncached_list_del(rt);

	idev = rt->rt6i_idev;
	if (idev) {
		rt->rt6i_idev = NULL;
		in6_dev_put(idev);
	}

	rcu_read_lock();
	from = rcu_dereference(rt->from);
	rcu_assign_pointer(rt->from, NULL);
	fib6_info_release(from);
	rcu_read_unlock();
}