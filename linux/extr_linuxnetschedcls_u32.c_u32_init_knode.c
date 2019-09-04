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
struct tcf_proto {int dummy; } ;
struct tc_u32_sel {int nkeys; } ;
struct tc_u_knode {int /*<<< orphan*/  exts; struct tc_u32_sel sel; struct tcf_proto* tp; struct tc_u_hnode* ht_down; int /*<<< orphan*/  flags; int /*<<< orphan*/  res; int /*<<< orphan*/  fshift; struct tc_u_hnode* ht_up; int /*<<< orphan*/  handle; struct tc_u_hnode* next; } ;
struct tc_u_hnode {int /*<<< orphan*/  refcnt; } ;
struct tc_u32_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct tc_u_hnode*,struct tc_u_hnode*) ; 
 int /*<<< orphan*/  TCA_U32_ACT ; 
 int /*<<< orphan*/  TCA_U32_POLICE ; 
 int /*<<< orphan*/  kfree (struct tc_u_knode*) ; 
 struct tc_u_knode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tc_u32_sel*,struct tc_u32_sel*,int) ; 
 struct tc_u_hnode* rtnl_dereference (struct tc_u_hnode*) ; 
 scalar_t__ tcf_exts_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tc_u_knode *u32_init_knode(struct tcf_proto *tp,
					 struct tc_u_knode *n)
{
	struct tc_u_hnode *ht = rtnl_dereference(n->ht_down);
	struct tc_u32_sel *s = &n->sel;
	struct tc_u_knode *new;

	new = kzalloc(sizeof(*n) + s->nkeys*sizeof(struct tc_u32_key),
		      GFP_KERNEL);

	if (!new)
		return NULL;

	RCU_INIT_POINTER(new->next, n->next);
	new->handle = n->handle;
	RCU_INIT_POINTER(new->ht_up, n->ht_up);

#ifdef CONFIG_NET_CLS_IND
	new->ifindex = n->ifindex;
#endif
	new->fshift = n->fshift;
	new->res = n->res;
	new->flags = n->flags;
	RCU_INIT_POINTER(new->ht_down, ht);

	/* bump reference count as long as we hold pointer to structure */
	if (ht)
		ht->refcnt++;

#ifdef CONFIG_CLS_U32_PERF
	/* Statistics may be incremented by readers during update
	 * so we must keep them in tact. When the node is later destroyed
	 * a special destroy call must be made to not free the pf memory.
	 */
	new->pf = n->pf;
#endif

#ifdef CONFIG_CLS_U32_MARK
	new->val = n->val;
	new->mask = n->mask;
	/* Similarly success statistics must be moved as pointers */
	new->pcpu_success = n->pcpu_success;
#endif
	new->tp = tp;
	memcpy(&new->sel, s, sizeof(*s) + s->nkeys*sizeof(struct tc_u32_key));

	if (tcf_exts_init(&new->exts, TCA_U32_ACT, TCA_U32_POLICE)) {
		kfree(new);
		return NULL;
	}

	return new;
}