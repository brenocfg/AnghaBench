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
struct tc_u_knode {int /*<<< orphan*/  exts; struct tc_u32_sel sel; int /*<<< orphan*/  pcpu_success; int /*<<< orphan*/  mask; int /*<<< orphan*/  val; int /*<<< orphan*/  pf; struct tc_u_hnode* ht_down; int /*<<< orphan*/  flags; int /*<<< orphan*/  res; int /*<<< orphan*/  fshift; int /*<<< orphan*/  ifindex; struct tc_u_hnode* ht_up; int /*<<< orphan*/  handle; struct tc_u_hnode* next; } ;
struct tc_u_hnode {int /*<<< orphan*/  refcnt; } ;
struct tc_u32_key {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct tc_u_hnode*,struct tc_u_hnode*) ; 
 int /*<<< orphan*/  TCA_U32_ACT ; 
 int /*<<< orphan*/  TCA_U32_POLICE ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  kfree (struct tc_u_knode*) ; 
 struct tc_u_knode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tc_u32_sel*,struct tc_u32_sel*,int /*<<< orphan*/ ) ; 
 struct tc_u_hnode* rtnl_dereference (struct tc_u_hnode*) ; 
 int /*<<< orphan*/  struct_size (struct tc_u32_sel*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcf_exts_init (int /*<<< orphan*/ *,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tc_u_knode *u32_init_knode(struct net *net, struct tcf_proto *tp,
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

	new->ifindex = n->ifindex;
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
	memcpy(&new->sel, s, struct_size(s, keys, s->nkeys));

	if (tcf_exts_init(&new->exts, net, TCA_U32_ACT, TCA_U32_POLICE)) {
		kfree(new);
		return NULL;
	}

	return new;
}