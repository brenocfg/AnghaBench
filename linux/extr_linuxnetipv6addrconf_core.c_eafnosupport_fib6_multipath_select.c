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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct flowi6 {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct fib6_info *
eafnosupport_fib6_multipath_select(const struct net *net, struct fib6_info *f6i,
				   struct flowi6 *fl6, int oif,
				   const struct sk_buff *skb, int strict)
{
	return f6i;
}