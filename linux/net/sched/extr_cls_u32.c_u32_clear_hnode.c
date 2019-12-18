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
struct tcf_proto {struct tc_u_common* data; } ;
struct tc_u_knode {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  handle; int /*<<< orphan*/  res; int /*<<< orphan*/  next; } ;
struct tc_u_hnode {unsigned int divisor; int /*<<< orphan*/  handle_idr; int /*<<< orphan*/ * ht; } ;
struct tc_u_common {int /*<<< orphan*/  knodes; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct tc_u_knode*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tc_u_knode* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32_delete_key_freepf_work ; 
 int /*<<< orphan*/  u32_destroy_key (struct tc_u_knode*,int) ; 
 int /*<<< orphan*/  u32_remove_hw_knode (struct tcf_proto*,struct tc_u_knode*,struct netlink_ext_ack*) ; 

__attribute__((used)) static void u32_clear_hnode(struct tcf_proto *tp, struct tc_u_hnode *ht,
			    struct netlink_ext_ack *extack)
{
	struct tc_u_common *tp_c = tp->data;
	struct tc_u_knode *n;
	unsigned int h;

	for (h = 0; h <= ht->divisor; h++) {
		while ((n = rtnl_dereference(ht->ht[h])) != NULL) {
			RCU_INIT_POINTER(ht->ht[h],
					 rtnl_dereference(n->next));
			tp_c->knodes--;
			tcf_unbind_filter(tp, &n->res);
			u32_remove_hw_knode(tp, n, extack);
			idr_remove(&ht->handle_idr, n->handle);
			if (tcf_exts_get_net(&n->exts))
				tcf_queue_work(&n->rwork, u32_delete_key_freepf_work);
			else
				u32_destroy_key(n, true);
		}
	}
}