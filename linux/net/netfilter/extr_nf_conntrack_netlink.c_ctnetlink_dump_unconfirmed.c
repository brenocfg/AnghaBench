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
 int ctnetlink_dump_list (struct sk_buff*,struct netlink_callback*,int) ; 

__attribute__((used)) static int
ctnetlink_dump_unconfirmed(struct sk_buff *skb, struct netlink_callback *cb)
{
	return ctnetlink_dump_list(skb, cb, false);
}