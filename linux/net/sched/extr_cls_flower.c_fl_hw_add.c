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
struct tcf_proto {int /*<<< orphan*/  lock; } ;
struct flow_cls_offload {scalar_t__ cookie; } ;
struct cls_fl_head {int /*<<< orphan*/  hw_filters; } ;
struct cls_fl_filter {int /*<<< orphan*/  hw_list; } ;

/* Variables and functions */
 struct cls_fl_head* fl_head_dereference (struct tcf_proto*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fl_hw_add(struct tcf_proto *tp, void *type_data)
{
	struct flow_cls_offload *cls_flower = type_data;
	struct cls_fl_filter *f =
		(struct cls_fl_filter *) cls_flower->cookie;
	struct cls_fl_head *head = fl_head_dereference(tp);

	spin_lock(&tp->lock);
	list_add(&f->hw_list, &head->hw_filters);
	spin_unlock(&tp->lock);
}