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
struct netlink_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ip6mr_fill_mroute ; 
 int /*<<< orphan*/  ip6mr_mr_table_iter ; 
 int /*<<< orphan*/  mfc_unres_lock ; 
 int mr_rtm_dumproute (struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip6mr_rtm_dumproute(struct sk_buff *skb, struct netlink_callback *cb)
{
	return mr_rtm_dumproute(skb, cb, ip6mr_mr_table_iter,
				_ip6mr_fill_mroute, &mfc_unres_lock);
}