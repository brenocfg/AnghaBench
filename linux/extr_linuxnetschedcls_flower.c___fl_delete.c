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
struct cls_fl_head {int /*<<< orphan*/  handle_idr; } ;
struct cls_fl_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  res; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  list; int /*<<< orphan*/  handle; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fl_destroy_filter (struct cls_fl_filter*) ; 
 int /*<<< orphan*/  fl_destroy_filter_work ; 
 int /*<<< orphan*/  fl_hw_destroy_filter (struct tcf_proto*,struct cls_fl_filter*,struct netlink_ext_ack*) ; 
 int fl_mask_put (struct cls_fl_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct cls_fl_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_skip_hw (int /*<<< orphan*/ ) ; 
 int tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __fl_delete(struct tcf_proto *tp, struct cls_fl_filter *f,
			struct netlink_ext_ack *extack)
{
	struct cls_fl_head *head = rtnl_dereference(tp->root);
	bool async = tcf_exts_get_net(&f->exts);
	bool last;

	idr_remove(&head->handle_idr, f->handle);
	list_del_rcu(&f->list);
	last = fl_mask_put(head, f->mask, async);
	if (!tc_skip_hw(f->flags))
		fl_hw_destroy_filter(tp, f, extack);
	tcf_unbind_filter(tp, &f->res);
	if (async)
		tcf_queue_work(&f->rwork, fl_destroy_filter_work);
	else
		__fl_destroy_filter(f);

	return last;
}