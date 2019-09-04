#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct rt6_info {TYPE_1__ rt6i_dst; TYPE_5__ dst; int /*<<< orphan*/  rt6i_prefsrc; } ;
struct rt6_exception_bucket {scalar_t__ depth; int /*<<< orphan*/  chain; } ;
struct rt6_exception {int /*<<< orphan*/  hlist; int /*<<< orphan*/  stamp; struct rt6_info* rt6i; } ;
struct TYPE_8__ {TYPE_2__* rt6_stats; } ;
struct net {TYPE_3__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct fib6_info {TYPE_4__* fib6_table; int /*<<< orphan*/  fib6_prefsrc; int /*<<< orphan*/  rt6i_exception_bucket; scalar_t__ exception_bucket_flushed; } ;
struct TYPE_9__ {int /*<<< orphan*/  tb6_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  fib_rt_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIB6_EXCEPTION_BUCKET_SIZE ; 
 scalar_t__ FIB6_MAX_DEPTH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTAX_MTU ; 
 struct rt6_exception* __rt6_find_exception_spinlock (struct rt6_exception_bucket**,int /*<<< orphan*/ *,struct in6_addr*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ dst_metric_raw (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_force_start_gc (struct net*) ; 
 scalar_t__ fib6_mtu (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_update_sernum (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rt6_exception_bucket* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rt6_exception* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct rt6_exception_bucket*) ; 
 struct rt6_exception_bucket* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_exception_lock ; 
 int /*<<< orphan*/  rt6_exception_remove_oldest (struct rt6_exception_bucket*) ; 
 int /*<<< orphan*/  rt6_remove_exception (struct rt6_exception_bucket*,struct rt6_exception*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt6_insert_exception(struct rt6_info *nrt,
				struct fib6_info *ort)
{
	struct net *net = dev_net(nrt->dst.dev);
	struct rt6_exception_bucket *bucket;
	struct in6_addr *src_key = NULL;
	struct rt6_exception *rt6_ex;
	int err = 0;

	spin_lock_bh(&rt6_exception_lock);

	if (ort->exception_bucket_flushed) {
		err = -EINVAL;
		goto out;
	}

	bucket = rcu_dereference_protected(ort->rt6i_exception_bucket,
					lockdep_is_held(&rt6_exception_lock));
	if (!bucket) {
		bucket = kcalloc(FIB6_EXCEPTION_BUCKET_SIZE, sizeof(*bucket),
				 GFP_ATOMIC);
		if (!bucket) {
			err = -ENOMEM;
			goto out;
		}
		rcu_assign_pointer(ort->rt6i_exception_bucket, bucket);
	}

#ifdef CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates ort is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	if (ort->fib6_src.plen)
		src_key = &nrt->rt6i_src.addr;
#endif

	/* Update rt6i_prefsrc as it could be changed
	 * in rt6_remove_prefsrc()
	 */
	nrt->rt6i_prefsrc = ort->fib6_prefsrc;
	/* rt6_mtu_change() might lower mtu on ort.
	 * Only insert this exception route if its mtu
	 * is less than ort's mtu value.
	 */
	if (dst_metric_raw(&nrt->dst, RTAX_MTU) >= fib6_mtu(ort)) {
		err = -EINVAL;
		goto out;
	}

	rt6_ex = __rt6_find_exception_spinlock(&bucket, &nrt->rt6i_dst.addr,
					       src_key);
	if (rt6_ex)
		rt6_remove_exception(bucket, rt6_ex);

	rt6_ex = kzalloc(sizeof(*rt6_ex), GFP_ATOMIC);
	if (!rt6_ex) {
		err = -ENOMEM;
		goto out;
	}
	rt6_ex->rt6i = nrt;
	rt6_ex->stamp = jiffies;
	hlist_add_head_rcu(&rt6_ex->hlist, &bucket->chain);
	bucket->depth++;
	net->ipv6.rt6_stats->fib_rt_cache++;

	if (bucket->depth > FIB6_MAX_DEPTH)
		rt6_exception_remove_oldest(bucket);

out:
	spin_unlock_bh(&rt6_exception_lock);

	/* Update fn->fn_sernum to invalidate all cached dst */
	if (!err) {
		spin_lock_bh(&ort->fib6_table->tb6_lock);
		fib6_update_sernum(net, ort);
		spin_unlock_bh(&ort->fib6_table->tb6_lock);
		fib6_force_start_gc(net);
	}

	return err;
}