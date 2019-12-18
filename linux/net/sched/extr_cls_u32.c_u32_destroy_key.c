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
struct tc_u_knode {scalar_t__ refcnt; int /*<<< orphan*/  pcpu_success; int /*<<< orphan*/  pf; int /*<<< orphan*/  exts; int /*<<< orphan*/  ht_down; } ;
struct tc_u_hnode {scalar_t__ refcnt; int /*<<< orphan*/  pcpu_success; int /*<<< orphan*/  pf; int /*<<< orphan*/  exts; int /*<<< orphan*/  ht_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc_u_knode*) ; 
 struct tc_u_knode* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u32_destroy_key(struct tc_u_knode *n, bool free_pf)
{
	struct tc_u_hnode *ht = rtnl_dereference(n->ht_down);

	tcf_exts_destroy(&n->exts);
	tcf_exts_put_net(&n->exts);
	if (ht && --ht->refcnt == 0)
		kfree(ht);
#ifdef CONFIG_CLS_U32_PERF
	if (free_pf)
		free_percpu(n->pf);
#endif
#ifdef CONFIG_CLS_U32_MARK
	if (free_pf)
		free_percpu(n->pcpu_success);
#endif
	kfree(n);
	return 0;
}