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
struct sock {int dummy; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; } ;
struct ipv6_pinfo {int /*<<< orphan*/  saddr_cache; int /*<<< orphan*/  daddr_cache; } ;
struct flowi6 {int flowi6_flags; scalar_t__ flowi6_oif; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct dst_entry {TYPE_2__* dev; TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ ifindex; } ;
struct TYPE_3__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int FLOWI_FLAG_SKIP_NH_OIF ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ ip6_rt_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dst_entry *ip6_sk_dst_check(struct sock *sk,
					  struct dst_entry *dst,
					  const struct flowi6 *fl6)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct rt6_info *rt;

	if (!dst)
		goto out;

	if (dst->ops->family != AF_INET6) {
		dst_release(dst);
		return NULL;
	}

	rt = (struct rt6_info *)dst;
	/* Yes, checking route validity in not connected
	 * case is not very simple. Take into account,
	 * that we do not support routing by source, TOS,
	 * and MSG_DONTROUTE		--ANK (980726)
	 *
	 * 1. ip6_rt_check(): If route was host route,
	 *    check that cached destination is current.
	 *    If it is network route, we still may
	 *    check its validity using saved pointer
	 *    to the last used address: daddr_cache.
	 *    We do not want to save whole address now,
	 *    (because main consumer of this service
	 *    is tcp, which has not this problem),
	 *    so that the last trick works only on connected
	 *    sockets.
	 * 2. oif also should be the same.
	 */
	if (ip6_rt_check(&rt->rt6i_dst, &fl6->daddr, np->daddr_cache) ||
#ifdef CONFIG_IPV6_SUBTREES
	    ip6_rt_check(&rt->rt6i_src, &fl6->saddr, np->saddr_cache) ||
#endif
	   (!(fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF) &&
	      (fl6->flowi6_oif && fl6->flowi6_oif != dst->dev->ifindex))) {
		dst_release(dst);
		dst = NULL;
	}

out:
	return dst;
}