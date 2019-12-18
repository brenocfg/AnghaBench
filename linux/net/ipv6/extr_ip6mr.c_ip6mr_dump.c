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
struct notifier_block {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTNL_FAMILY_IP6MR ; 
 int /*<<< orphan*/  ip6mr_mr_table_iter ; 
 int /*<<< orphan*/  ip6mr_rules_dump ; 
 int mr_dump (struct net*,struct notifier_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrt_lock ; 

__attribute__((used)) static int ip6mr_dump(struct net *net, struct notifier_block *nb)
{
	return mr_dump(net, nb, RTNL_FAMILY_IP6MR, ip6mr_rules_dump,
		       ip6mr_mr_table_iter, &mrt_lock);
}