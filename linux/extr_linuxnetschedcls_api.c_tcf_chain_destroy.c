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
struct TYPE_2__ {int /*<<< orphan*/ * chain; } ;
struct tcf_chain {scalar_t__ refcnt; int /*<<< orphan*/  chain_list; TYPE_1__ chain0; int /*<<< orphan*/  index; int /*<<< orphan*/  list; struct tcf_chain* block; } ;
struct tcf_block {scalar_t__ refcnt; int /*<<< orphan*/  chain_list; TYPE_1__ chain0; int /*<<< orphan*/  index; int /*<<< orphan*/  list; struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tcf_chain*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_chain_destroy(struct tcf_chain *chain)
{
	struct tcf_block *block = chain->block;

	list_del(&chain->list);
	if (!chain->index)
		block->chain0.chain = NULL;
	kfree(chain);
	if (list_empty(&block->chain_list) && block->refcnt == 0)
		kfree(block);
}