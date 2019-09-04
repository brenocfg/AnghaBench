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
struct netlink_callback {struct genl_ops* data; } ;
struct genl_ops {int (* dumpit ) (struct sk_buff*,struct netlink_callback*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int stub1 (struct sk_buff*,struct netlink_callback*) ; 

__attribute__((used)) static int genl_lock_dumpit(struct sk_buff *skb, struct netlink_callback *cb)
{
	/* our ops are always const - netlink API doesn't propagate that */
	const struct genl_ops *ops = cb->data;
	int rc;

	genl_lock();
	rc = ops->dumpit(skb, cb);
	genl_unlock();
	return rc;
}