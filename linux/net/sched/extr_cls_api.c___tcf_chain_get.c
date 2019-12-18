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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_chain {int action_refcnt; int refcnt; } ;
struct tcf_block {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int /*<<< orphan*/  RTM_NEWCHAIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_chain_notify (struct tcf_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct tcf_chain* tcf_chain_create (struct tcf_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_chain_hold (struct tcf_chain*) ; 
 struct tcf_chain* tcf_chain_lookup (struct tcf_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tcf_chain *__tcf_chain_get(struct tcf_block *block,
					 u32 chain_index, bool create,
					 bool by_act)
{
	struct tcf_chain *chain = NULL;
	bool is_first_reference;

	mutex_lock(&block->lock);
	chain = tcf_chain_lookup(block, chain_index);
	if (chain) {
		tcf_chain_hold(chain);
	} else {
		if (!create)
			goto errout;
		chain = tcf_chain_create(block, chain_index);
		if (!chain)
			goto errout;
	}

	if (by_act)
		++chain->action_refcnt;
	is_first_reference = chain->refcnt - chain->action_refcnt == 1;
	mutex_unlock(&block->lock);

	/* Send notification only in case we got the first
	 * non-action reference. Until then, the chain acts only as
	 * a placeholder for actions pointing to it and user ought
	 * not know about them.
	 */
	if (is_first_reference && !by_act)
		tc_chain_notify(chain, NULL, 0, NLM_F_CREATE | NLM_F_EXCL,
				RTM_NEWCHAIN, false);

	return chain;

errout:
	mutex_unlock(&block->lock);
	return chain;
}