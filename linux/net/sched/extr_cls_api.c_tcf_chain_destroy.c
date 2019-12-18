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
struct tcf_chain {int /*<<< orphan*/  filter_chain_lock; struct tcf_block* block; } ;
struct tcf_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct tcf_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  tcf_block_destroy (struct tcf_block*) ; 

__attribute__((used)) static void tcf_chain_destroy(struct tcf_chain *chain, bool free_block)
{
	struct tcf_block *block = chain->block;

	mutex_destroy(&chain->filter_chain_lock);
	kfree_rcu(chain, rcu);
	if (free_block)
		tcf_block_destroy(block);
}