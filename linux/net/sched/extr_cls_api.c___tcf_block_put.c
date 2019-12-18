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
struct tcf_block_ext_info {int dummy; } ;
struct tcf_block {int /*<<< orphan*/  net; int /*<<< orphan*/  lock; int /*<<< orphan*/  chain_list; int /*<<< orphan*/  refcnt; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_block_destroy (struct tcf_block*) ; 
 int /*<<< orphan*/  tcf_block_flush_all_chains (struct tcf_block*,int) ; 
 int /*<<< orphan*/  tcf_block_offload_unbind (struct tcf_block*,struct Qdisc*,struct tcf_block_ext_info*) ; 
 int /*<<< orphan*/  tcf_block_remove (struct tcf_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_block_shared (struct tcf_block*) ; 

__attribute__((used)) static void __tcf_block_put(struct tcf_block *block, struct Qdisc *q,
			    struct tcf_block_ext_info *ei, bool rtnl_held)
{
	if (refcount_dec_and_mutex_lock(&block->refcnt, &block->lock)) {
		/* Flushing/putting all chains will cause the block to be
		 * deallocated when last chain is freed. However, if chain_list
		 * is empty, block has to be manually deallocated. After block
		 * reference counter reached 0, it is no longer possible to
		 * increment it or add new chains to block.
		 */
		bool free_block = list_empty(&block->chain_list);

		mutex_unlock(&block->lock);
		if (tcf_block_shared(block))
			tcf_block_remove(block, block->net);

		if (q)
			tcf_block_offload_unbind(block, q, ei);

		if (free_block)
			tcf_block_destroy(block);
		else
			tcf_block_flush_all_chains(block, rtnl_held);
	} else if (q) {
		tcf_block_offload_unbind(block, q, ei);
	}
}