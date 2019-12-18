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
struct tcf_chain {int /*<<< orphan*/  index; int /*<<< orphan*/  list; struct tcf_block* block; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chain; } ;
struct tcf_block {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  chain_list; TYPE_1__ chain0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BLOCK_LOCKED (struct tcf_block*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tcf_chain_detach(struct tcf_chain *chain)
{
	struct tcf_block *block = chain->block;

	ASSERT_BLOCK_LOCKED(block);

	list_del(&chain->list);
	if (!chain->index)
		block->chain0.chain = NULL;

	if (list_empty(&block->chain_list) &&
	    refcount_read(&block->refcnt) == 0)
		return true;

	return false;
}