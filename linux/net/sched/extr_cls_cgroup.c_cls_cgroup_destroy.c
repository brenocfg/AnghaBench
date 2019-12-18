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
struct cls_cgroup_head {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cls_cgroup_destroy (struct cls_cgroup_head*) ; 
 int /*<<< orphan*/  cls_cgroup_destroy_work ; 
 struct cls_cgroup_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cls_cgroup_destroy(struct tcf_proto *tp, bool rtnl_held,
			       struct netlink_ext_ack *extack)
{
	struct cls_cgroup_head *head = rtnl_dereference(tp->root);

	/* Head can still be NULL due to cls_cgroup_init(). */
	if (head) {
		if (tcf_exts_get_net(&head->exts))
			tcf_queue_work(&head->rwork, cls_cgroup_destroy_work);
		else
			__cls_cgroup_destroy(head);
	}
}