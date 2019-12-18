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
struct nft_rule {int dummy; } ;
struct nft_chain {struct nft_rule** rules_next; int /*<<< orphan*/  rules_gen_0; int /*<<< orphan*/  rules_gen_1; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_commit_lock_is_held (struct net*) ; 
 int /*<<< orphan*/  nf_tables_commit_chain_free_rules_old (struct nft_rule**) ; 
 int nft_gencursor_next (struct net*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nft_rule**) ; 
 struct nft_rule** rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_commit_chain(struct net *net, struct nft_chain *chain)
{
	struct nft_rule **g0, **g1;
	bool next_genbit;

	next_genbit = nft_gencursor_next(net);

	g0 = rcu_dereference_protected(chain->rules_gen_0,
				       lockdep_commit_lock_is_held(net));
	g1 = rcu_dereference_protected(chain->rules_gen_1,
				       lockdep_commit_lock_is_held(net));

	/* No changes to this chain? */
	if (chain->rules_next == NULL) {
		/* chain had no change in last or next generation */
		if (g0 == g1)
			return;
		/*
		 * chain had no change in this generation; make sure next
		 * one uses same rules as current generation.
		 */
		if (next_genbit) {
			rcu_assign_pointer(chain->rules_gen_1, g0);
			nf_tables_commit_chain_free_rules_old(g1);
		} else {
			rcu_assign_pointer(chain->rules_gen_0, g1);
			nf_tables_commit_chain_free_rules_old(g0);
		}

		return;
	}

	if (next_genbit)
		rcu_assign_pointer(chain->rules_gen_1, chain->rules_next);
	else
		rcu_assign_pointer(chain->rules_gen_0, chain->rules_next);

	chain->rules_next = NULL;

	if (g0 == g1)
		return;

	if (next_genbit)
		nf_tables_commit_chain_free_rules_old(g1);
	else
		nf_tables_commit_chain_free_rules_old(g0);
}