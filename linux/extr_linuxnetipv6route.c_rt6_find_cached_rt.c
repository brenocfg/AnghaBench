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
struct rt6_exception_bucket {int dummy; } ;
struct rt6_exception {struct rt6_info* rt6i; } ;
struct in6_addr {int dummy; } ;
struct fib6_info {int /*<<< orphan*/  rt6i_exception_bucket; } ;

/* Variables and functions */
 struct rt6_exception* __rt6_find_exception_rcu (struct rt6_exception_bucket**,struct in6_addr*,struct in6_addr*) ; 
 struct rt6_exception_bucket* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_check_expired (struct rt6_info*) ; 

__attribute__((used)) static struct rt6_info *rt6_find_cached_rt(struct fib6_info *rt,
					   struct in6_addr *daddr,
					   struct in6_addr *saddr)
{
	struct rt6_exception_bucket *bucket;
	struct in6_addr *src_key = NULL;
	struct rt6_exception *rt6_ex;
	struct rt6_info *res = NULL;

	bucket = rcu_dereference(rt->rt6i_exception_bucket);

#ifdef CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates rt is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	if (rt->fib6_src.plen)
		src_key = saddr;
#endif
	rt6_ex = __rt6_find_exception_rcu(&bucket, daddr, src_key);

	if (rt6_ex && !rt6_check_expired(rt6_ex->rt6i))
		res = rt6_ex->rt6i;

	return res;
}