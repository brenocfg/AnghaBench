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
struct tcf_proto {struct tc_u_common* data; int /*<<< orphan*/  root; int /*<<< orphan*/  prio; } ;
struct tc_u_hnode {int handle; int /*<<< orphan*/  refcnt; struct tc_u_common* tp_c; int /*<<< orphan*/  next; int /*<<< orphan*/  handle_idr; int /*<<< orphan*/  prio; } ;
struct tc_u_common {int /*<<< orphan*/  hlist; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  hnode; int /*<<< orphan*/  handle_idr; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gen_new_htid (struct tc_u_common*,struct tc_u_hnode*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tc_u_hnode*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tc_u_hnode*) ; 
 struct tc_u_common* tc_u_common_find (struct tcf_proto*) ; 
 int /*<<< orphan*/ * tc_u_common_hash ; 
 int /*<<< orphan*/  tc_u_common_ptr (struct tcf_proto*) ; 
 unsigned int tc_u_hash (struct tcf_proto*) ; 

__attribute__((used)) static int u32_init(struct tcf_proto *tp)
{
	struct tc_u_hnode *root_ht;
	struct tc_u_common *tp_c;
	unsigned int h;

	tp_c = tc_u_common_find(tp);

	root_ht = kzalloc(sizeof(*root_ht), GFP_KERNEL);
	if (root_ht == NULL)
		return -ENOBUFS;

	root_ht->refcnt++;
	root_ht->handle = tp_c ? gen_new_htid(tp_c, root_ht) : 0x80000000;
	root_ht->prio = tp->prio;
	idr_init(&root_ht->handle_idr);

	if (tp_c == NULL) {
		tp_c = kzalloc(sizeof(*tp_c), GFP_KERNEL);
		if (tp_c == NULL) {
			kfree(root_ht);
			return -ENOBUFS;
		}
		tp_c->ptr = tc_u_common_ptr(tp);
		INIT_HLIST_NODE(&tp_c->hnode);
		idr_init(&tp_c->handle_idr);

		h = tc_u_hash(tp);
		hlist_add_head(&tp_c->hnode, &tc_u_common_hash[h]);
	}

	tp_c->refcnt++;
	RCU_INIT_POINTER(root_ht->next, tp_c->hlist);
	rcu_assign_pointer(tp_c->hlist, root_ht);
	root_ht->tp_c = tp_c;

	root_ht->refcnt++;
	rcu_assign_pointer(tp->root, root_ht);
	tp->data = tp_c;
	return 0;
}