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
 struct tcf_chain* __tcf_get_next_chain (struct tcf_block*,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 

struct tcf_chain *
tcf_get_next_chain(struct tcf_block *block, struct tcf_chain *chain)
{
	struct tcf_chain *chain_next = __tcf_get_next_chain(block, chain);

	if (chain)
		tcf_chain_put(chain);

	return chain_next;
}