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
struct cls_fl_head {int /*<<< orphan*/  ht; int /*<<< orphan*/  handle_idr; int /*<<< orphan*/  masks; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct cls_fl_head* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cls_fl_head*) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fl_init(struct tcf_proto *tp)
{
	struct cls_fl_head *head;

	head = kzalloc(sizeof(*head), GFP_KERNEL);
	if (!head)
		return -ENOBUFS;

	INIT_LIST_HEAD_RCU(&head->masks);
	rcu_assign_pointer(tp->root, head);
	idr_init(&head->handle_idr);

	return rhashtable_init(&head->ht, &mask_ht_params);
}