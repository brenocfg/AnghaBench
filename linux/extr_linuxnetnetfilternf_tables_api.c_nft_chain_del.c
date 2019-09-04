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
struct nft_table {int /*<<< orphan*/  chains_ht; } ;
struct nft_chain {int /*<<< orphan*/  list; int /*<<< orphan*/  rhlhead; struct nft_table* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_chain_ht_params ; 
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_chain_del(struct nft_chain *chain)
{
	struct nft_table *table = chain->table;

	WARN_ON_ONCE(rhltable_remove(&table->chains_ht, &chain->rhlhead,
				     nft_chain_ht_params));
	list_del_rcu(&chain->list);
}