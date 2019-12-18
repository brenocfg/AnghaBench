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
struct rsvp_session {int /*<<< orphan*/ * ht; int /*<<< orphan*/  next; } ;
struct rsvp_head {int /*<<< orphan*/ * ht; int /*<<< orphan*/  next; } ;
struct rsvp_filter {int /*<<< orphan*/  next; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct rsvp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsvp_delete_filter (struct tcf_proto*,struct rsvp_filter*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsvp_destroy(struct tcf_proto *tp, bool rtnl_held,
			 struct netlink_ext_ack *extack)
{
	struct rsvp_head *data = rtnl_dereference(tp->root);
	int h1, h2;

	if (data == NULL)
		return;

	for (h1 = 0; h1 < 256; h1++) {
		struct rsvp_session *s;

		while ((s = rtnl_dereference(data->ht[h1])) != NULL) {
			RCU_INIT_POINTER(data->ht[h1], s->next);

			for (h2 = 0; h2 <= 16; h2++) {
				struct rsvp_filter *f;

				while ((f = rtnl_dereference(s->ht[h2])) != NULL) {
					rcu_assign_pointer(s->ht[h2], f->next);
					rsvp_delete_filter(tp, f);
				}
			}
			kfree_rcu(s, rcu);
		}
	}
	kfree_rcu(data, rcu);
}