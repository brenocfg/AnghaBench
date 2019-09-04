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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct rt6_info {int rt6i_flags; TYPE_1__ rt6i_dst; int /*<<< orphan*/  from; } ;
struct rt6_exception_bucket {int dummy; } ;
struct rt6_exception {int /*<<< orphan*/  stamp; } ;
struct in6_addr {int dummy; } ;
struct fib6_info {int /*<<< orphan*/  rt6i_exception_bucket; } ;

/* Variables and functions */
 int RTF_CACHE ; 
 struct rt6_exception* __rt6_find_exception_rcu (struct rt6_exception_bucket**,int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  jiffies ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void rt6_update_exception_stamp_rt(struct rt6_info *rt)
{
	struct rt6_exception_bucket *bucket;
	struct in6_addr *src_key = NULL;
	struct rt6_exception *rt6_ex;
	struct fib6_info *from;

	rcu_read_lock();
	from = rcu_dereference(rt->from);
	if (!from || !(rt->rt6i_flags & RTF_CACHE))
		goto unlock;

	bucket = rcu_dereference(from->rt6i_exception_bucket);

#ifdef CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates 'from' is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	if (from->fib6_src.plen)
		src_key = &rt->rt6i_src.addr;
#endif
	rt6_ex = __rt6_find_exception_rcu(&bucket,
					  &rt->rt6i_dst.addr,
					  src_key);
	if (rt6_ex)
		rt6_ex->stamp = jiffies;

unlock:
	rcu_read_unlock();
}