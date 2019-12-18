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
struct tcf_proto_ops {int dummy; } ;
struct tcf_chain {int explicitly_created; unsigned int action_refcnt; unsigned int refcnt; int flushing; int /*<<< orphan*/  index; void* tmplt_priv; struct tcf_proto_ops* tmplt_ops; struct tcf_block* block; } ;
struct tcf_block {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_chain_notify_delete (struct tcf_proto_ops const*,void*,int /*<<< orphan*/ ,struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tc_chain_tmplt_del (struct tcf_proto_ops const*,void*) ; 
 int /*<<< orphan*/  tcf_chain_destroy (struct tcf_chain*,int) ; 
 int tcf_chain_detach (struct tcf_chain*) ; 

__attribute__((used)) static void __tcf_chain_put(struct tcf_chain *chain, bool by_act,
			    bool explicitly_created)
{
	struct tcf_block *block = chain->block;
	const struct tcf_proto_ops *tmplt_ops;
	bool free_block = false;
	unsigned int refcnt;
	void *tmplt_priv;

	mutex_lock(&block->lock);
	if (explicitly_created) {
		if (!chain->explicitly_created) {
			mutex_unlock(&block->lock);
			return;
		}
		chain->explicitly_created = false;
	}

	if (by_act)
		chain->action_refcnt--;

	/* tc_chain_notify_delete can't be called while holding block lock.
	 * However, when block is unlocked chain can be changed concurrently, so
	 * save these to temporary variables.
	 */
	refcnt = --chain->refcnt;
	tmplt_ops = chain->tmplt_ops;
	tmplt_priv = chain->tmplt_priv;

	/* The last dropped non-action reference will trigger notification. */
	if (refcnt - chain->action_refcnt == 0 && !by_act) {
		tc_chain_notify_delete(tmplt_ops, tmplt_priv, chain->index,
				       block, NULL, 0, 0, false);
		/* Last reference to chain, no need to lock. */
		chain->flushing = false;
	}

	if (refcnt == 0)
		free_block = tcf_chain_detach(chain);
	mutex_unlock(&block->lock);

	if (refcnt == 0) {
		tc_chain_tmplt_del(tmplt_ops, tmplt_priv);
		tcf_chain_destroy(chain, free_block);
	}
}