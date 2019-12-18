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

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 scalar_t__ dst_hold_safe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ip6_hold_safe(struct net *net, struct rt6_info **prt)
{
	struct rt6_info *rt = *prt;

	if (dst_hold_safe(&rt->dst))
		return true;
	if (net) {
		rt = net->ipv6.ip6_null_entry;
		dst_hold(&rt->dst);
	} else {
		rt = NULL;
	}
	*prt = rt;
	return false;
}