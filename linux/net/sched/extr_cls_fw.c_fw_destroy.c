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
struct fw_head {int /*<<< orphan*/ * ht; } ;
struct fw_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int HTSIZE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  __fw_delete_filter (struct fw_filter*) ; 
 int /*<<< orphan*/  fw_delete_filter_work ; 
 int /*<<< orphan*/  kfree_rcu (struct fw_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fw_destroy(struct tcf_proto *tp, bool rtnl_held,
		       struct netlink_ext_ack *extack)
{
	struct fw_head *head = rtnl_dereference(tp->root);
	struct fw_filter *f;
	int h;

	if (head == NULL)
		return;

	for (h = 0; h < HTSIZE; h++) {
		while ((f = rtnl_dereference(head->ht[h])) != NULL) {
			RCU_INIT_POINTER(head->ht[h],
					 rtnl_dereference(f->next));
			tcf_unbind_filter(tp, &f->res);
			if (tcf_exts_get_net(&f->exts))
				tcf_queue_work(&f->rwork, fw_delete_filter_work);
			else
				__fw_delete_filter(f);
		}
	}
	kfree_rcu(head, rcu);
}