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
struct tcf_proto {int /*<<< orphan*/  lock; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_fl_head {int /*<<< orphan*/  handle_idr; } ;
struct cls_fl_filter {int deleted; int /*<<< orphan*/  res; int /*<<< orphan*/  flags; TYPE_1__* mask; int /*<<< orphan*/  list; int /*<<< orphan*/  handle; int /*<<< orphan*/  ht_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_ht_params; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __fl_put (struct cls_fl_filter*) ; 
 struct cls_fl_head* fl_head_dereference (struct tcf_proto*) ; 
 int /*<<< orphan*/  fl_hw_destroy_filter (struct tcf_proto*,struct cls_fl_filter*,int,struct netlink_ext_ack*) ; 
 int fl_mask_put (struct cls_fl_head*,TYPE_1__*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_skip_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __fl_delete(struct tcf_proto *tp, struct cls_fl_filter *f,
		       bool *last, bool rtnl_held,
		       struct netlink_ext_ack *extack)
{
	struct cls_fl_head *head = fl_head_dereference(tp);

	*last = false;

	spin_lock(&tp->lock);
	if (f->deleted) {
		spin_unlock(&tp->lock);
		return -ENOENT;
	}

	f->deleted = true;
	rhashtable_remove_fast(&f->mask->ht, &f->ht_node,
			       f->mask->filter_ht_params);
	idr_remove(&head->handle_idr, f->handle);
	list_del_rcu(&f->list);
	spin_unlock(&tp->lock);

	*last = fl_mask_put(head, f->mask);
	if (!tc_skip_hw(f->flags))
		fl_hw_destroy_filter(tp, f, rtnl_held, extack);
	tcf_unbind_filter(tp, &f->res);
	__fl_put(f);

	return 0;
}