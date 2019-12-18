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
struct rt6_info {int /*<<< orphan*/  rt6i_uncached; } ;
struct TYPE_4__ {TYPE_1__* ip6_null_entry; } ;
struct net {TYPE_2__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_3__ {struct dst_entry dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_hold_safe (struct dst_entry*) ; 
 struct dst_entry* ip6_route_output_flags_noref (struct net*,struct sock const*,struct flowi6*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct dst_entry *ip6_route_output_flags(struct net *net,
					 const struct sock *sk,
					 struct flowi6 *fl6,
					 int flags)
{
        struct dst_entry *dst;
        struct rt6_info *rt6;

        rcu_read_lock();
        dst = ip6_route_output_flags_noref(net, sk, fl6, flags);
        rt6 = (struct rt6_info *)dst;
        /* For dst cached in uncached_list, refcnt is already taken. */
        if (list_empty(&rt6->rt6i_uncached) && !dst_hold_safe(dst)) {
                dst = &net->ipv6.ip6_null_entry->dst;
                dst_hold(dst);
        }
        rcu_read_unlock();

        return dst;
}