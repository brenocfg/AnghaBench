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
struct cls_mall_head {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  flags; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mall_destroy (struct cls_mall_head*) ; 
 int /*<<< orphan*/  mall_destroy_hw_filter (struct tcf_proto*,struct cls_mall_head*,unsigned long,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mall_destroy_work ; 
 struct cls_mall_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_skip_hw (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mall_destroy(struct tcf_proto *tp, bool rtnl_held,
			 struct netlink_ext_ack *extack)
{
	struct cls_mall_head *head = rtnl_dereference(tp->root);

	if (!head)
		return;

	tcf_unbind_filter(tp, &head->res);

	if (!tc_skip_hw(head->flags))
		mall_destroy_hw_filter(tp, head, (unsigned long) head, extack);

	if (tcf_exts_get_net(&head->exts))
		tcf_queue_work(&head->rwork, mall_destroy_work);
	else
		__mall_destroy(head);
}