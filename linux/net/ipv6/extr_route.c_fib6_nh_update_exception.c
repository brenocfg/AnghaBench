#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {struct in6_addr addr; } ;
struct rt6_info {TYPE_2__ rt6i_dst; TYPE_1__ rt6i_src; } ;
struct rt6_exception_bucket {int dummy; } ;
struct rt6_exception {int /*<<< orphan*/  stamp; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 struct rt6_exception* __rt6_find_exception_rcu (struct rt6_exception_bucket**,int /*<<< orphan*/ *,struct in6_addr const*) ; 
 struct rt6_exception_bucket* fib6_nh_get_excptn_bucket (struct fib6_nh const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void fib6_nh_update_exception(const struct fib6_nh *nh, int plen,
				     const struct rt6_info *rt)
{
	const struct in6_addr *src_key = NULL;
	struct rt6_exception_bucket *bucket;
	struct rt6_exception *rt6_ex;

	bucket = fib6_nh_get_excptn_bucket(nh, NULL);
#ifdef CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates 'from' is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	if (plen)
		src_key = &rt->rt6i_src.addr;
#endif
	rt6_ex = __rt6_find_exception_rcu(&bucket, &rt->rt6i_dst.addr, src_key);
	if (rt6_ex)
		rt6_ex->stamp = jiffies;
}