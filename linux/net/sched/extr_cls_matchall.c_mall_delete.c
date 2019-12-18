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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_mall_head {int deleting; } ;

/* Variables and functions */
 struct cls_mall_head* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mall_delete(struct tcf_proto *tp, void *arg, bool *last,
		       bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct cls_mall_head *head = rtnl_dereference(tp->root);

	head->deleting = true;
	*last = true;
	return 0;
}