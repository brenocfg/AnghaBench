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
struct tcf_chain {int dummy; } ;
struct tcf_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcf_chain_flush (struct tcf_chain*,int) ; 
 int /*<<< orphan*/  tcf_chain_put_explicitly_created (struct tcf_chain*) ; 
 struct tcf_chain* tcf_get_next_chain (struct tcf_block*,struct tcf_chain*) ; 

__attribute__((used)) static void tcf_block_flush_all_chains(struct tcf_block *block, bool rtnl_held)
{
	struct tcf_chain *chain;

	/* Last reference to block. At this point chains cannot be added or
	 * removed concurrently.
	 */
	for (chain = tcf_get_next_chain(block, NULL);
	     chain;
	     chain = tcf_get_next_chain(block, chain)) {
		tcf_chain_put_explicitly_created(chain);
		tcf_chain_flush(chain, rtnl_held);
	}
}