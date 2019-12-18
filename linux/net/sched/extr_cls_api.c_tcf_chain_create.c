#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tcf_chain {int refcnt; int /*<<< orphan*/  index; struct tcf_block* block; int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct tcf_chain* chain; } ;
struct tcf_block {TYPE_1__ chain0; int /*<<< orphan*/  chain_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BLOCK_LOCKED (struct tcf_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tcf_chain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tcf_chain *tcf_chain_create(struct tcf_block *block,
					  u32 chain_index)
{
	struct tcf_chain *chain;

	ASSERT_BLOCK_LOCKED(block);

	chain = kzalloc(sizeof(*chain), GFP_KERNEL);
	if (!chain)
		return NULL;
	list_add_tail(&chain->list, &block->chain_list);
	mutex_init(&chain->filter_chain_lock);
	chain->block = block;
	chain->index = chain_index;
	chain->refcnt = 1;
	if (!chain->index)
		block->chain0.chain = chain;
	return chain;
}