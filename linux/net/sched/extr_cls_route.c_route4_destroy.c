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
struct route4_head {int /*<<< orphan*/ * table; int /*<<< orphan*/ * ht; } ;
struct route4_filter {int /*<<< orphan*/  exts; int /*<<< orphan*/  res; int /*<<< orphan*/  next; } ;
struct route4_bucket {int /*<<< orphan*/ * table; int /*<<< orphan*/ * ht; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct route4_filter*) ; 
 int /*<<< orphan*/  __route4_delete_filter (struct route4_filter*) ; 
 int /*<<< orphan*/  kfree_rcu (struct route4_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  route4_queue_work (struct route4_filter*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void route4_destroy(struct tcf_proto *tp, bool rtnl_held,
			   struct netlink_ext_ack *extack)
{
	struct route4_head *head = rtnl_dereference(tp->root);
	int h1, h2;

	if (head == NULL)
		return;

	for (h1 = 0; h1 <= 256; h1++) {
		struct route4_bucket *b;

		b = rtnl_dereference(head->table[h1]);
		if (b) {
			for (h2 = 0; h2 <= 32; h2++) {
				struct route4_filter *f;

				while ((f = rtnl_dereference(b->ht[h2])) != NULL) {
					struct route4_filter *next;

					next = rtnl_dereference(f->next);
					RCU_INIT_POINTER(b->ht[h2], next);
					tcf_unbind_filter(tp, &f->res);
					if (tcf_exts_get_net(&f->exts))
						route4_queue_work(f);
					else
						__route4_delete_filter(f);
				}
			}
			RCU_INIT_POINTER(head->table[h1], NULL);
			kfree_rcu(b, rcu);
		}
	}
	kfree_rcu(head, rcu);
}