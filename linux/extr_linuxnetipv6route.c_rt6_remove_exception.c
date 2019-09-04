#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rt6_exception_bucket {int /*<<< orphan*/  depth; } ;
struct rt6_exception {TYPE_3__* rt6i; int /*<<< orphan*/  hlist; } ;
struct TYPE_7__ {TYPE_1__* rt6_stats; } ;
struct net {TYPE_2__ ipv6; } ;
struct fib6_info {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_4__ dst; int /*<<< orphan*/  from; } ;
struct TYPE_6__ {int /*<<< orphan*/  fib_rt_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_dev_put (TYPE_4__*) ; 
 int /*<<< orphan*/  dst_release (TYPE_4__*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct rt6_exception*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fib6_info* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_exception_lock ; 

__attribute__((used)) static void rt6_remove_exception(struct rt6_exception_bucket *bucket,
				 struct rt6_exception *rt6_ex)
{
	struct fib6_info *from;
	struct net *net;

	if (!bucket || !rt6_ex)
		return;

	net = dev_net(rt6_ex->rt6i->dst.dev);
	net->ipv6.rt6_stats->fib_rt_cache--;

	/* purge completely the exception to allow releasing the held resources:
	 * some [sk] cache may keep the dst around for unlimited time
	 */
	from = rcu_dereference_protected(rt6_ex->rt6i->from,
					 lockdep_is_held(&rt6_exception_lock));
	rcu_assign_pointer(rt6_ex->rt6i->from, NULL);
	fib6_info_release(from);
	dst_dev_put(&rt6_ex->rt6i->dst);

	hlist_del_rcu(&rt6_ex->hlist);
	dst_release(&rt6_ex->rt6i->dst);
	kfree_rcu(rt6_ex, rcu);
	WARN_ON_ONCE(!bucket->depth);
	bucket->depth--;
}