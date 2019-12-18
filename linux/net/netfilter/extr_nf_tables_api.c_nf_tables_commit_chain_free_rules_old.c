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
struct nft_rules_old {int /*<<< orphan*/  h; struct nft_rule** start; } ;
struct nft_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nf_tables_commit_chain_free_rules_old ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_commit_chain_free_rules_old(struct nft_rule **rules)
{
	struct nft_rule **r = rules;
	struct nft_rules_old *old;

	while (*r)
		r++;

	r++;	/* rcu_head is after end marker */
	old = (void *) r;
	old->start = rules;

	call_rcu(&old->h, __nf_tables_commit_chain_free_rules_old);
}