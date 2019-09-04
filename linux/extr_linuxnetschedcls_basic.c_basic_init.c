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
struct basic_head {int /*<<< orphan*/  handle_idr; int /*<<< orphan*/  flist; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct basic_head* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct basic_head*) ; 

__attribute__((used)) static int basic_init(struct tcf_proto *tp)
{
	struct basic_head *head;

	head = kzalloc(sizeof(*head), GFP_KERNEL);
	if (head == NULL)
		return -ENOBUFS;
	INIT_LIST_HEAD(&head->flist);
	idr_init(&head->handle_idr);
	rcu_assign_pointer(tp->root, head);
	return 0;
}