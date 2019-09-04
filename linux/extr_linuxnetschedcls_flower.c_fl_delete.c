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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_fl_head {int /*<<< orphan*/  masks; } ;
struct cls_fl_filter {TYPE_1__* mask; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_ht_params; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fl_delete (struct tcf_proto*,struct cls_fl_filter*,struct netlink_ext_ack*) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cls_fl_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_skip_sw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_delete(struct tcf_proto *tp, void *arg, bool *last,
		     struct netlink_ext_ack *extack)
{
	struct cls_fl_head *head = rtnl_dereference(tp->root);
	struct cls_fl_filter *f = arg;

	if (!tc_skip_sw(f->flags))
		rhashtable_remove_fast(&f->mask->ht, &f->ht_node,
				       f->mask->filter_ht_params);
	__fl_delete(tp, f, extack);
	*last = list_empty(&head->masks);
	return 0;
}