#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* chain; TYPE_1__* table; } ;
struct nft_trans {TYPE_2__ ctx; } ;
struct nft_base_chain {int policy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rhlhead; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  chains_ht; } ;

/* Variables and functions */
#define  NF_ACCEPT 129 
#define  NF_DROP 128 
 struct nft_base_chain* nft_base_chain (TYPE_3__*) ; 
 int /*<<< orphan*/  nft_chain_ht_params ; 
 int /*<<< orphan*/  nft_chain_stats_replace (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_is_base_chain (TYPE_3__*) ; 
 scalar_t__ nft_trans_chain_name (struct nft_trans*) ; 
 int nft_trans_chain_policy (struct nft_trans*) ; 
 int /*<<< orphan*/  rhltable_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nft_chain_commit_update(struct nft_trans *trans)
{
	struct nft_base_chain *basechain;

	if (nft_trans_chain_name(trans)) {
		rhltable_remove(&trans->ctx.table->chains_ht,
				&trans->ctx.chain->rhlhead,
				nft_chain_ht_params);
		swap(trans->ctx.chain->name, nft_trans_chain_name(trans));
		rhltable_insert_key(&trans->ctx.table->chains_ht,
				    trans->ctx.chain->name,
				    &trans->ctx.chain->rhlhead,
				    nft_chain_ht_params);
	}

	if (!nft_is_base_chain(trans->ctx.chain))
		return;

	nft_chain_stats_replace(trans);

	basechain = nft_base_chain(trans->ctx.chain);

	switch (nft_trans_chain_policy(trans)) {
	case NF_DROP:
	case NF_ACCEPT:
		basechain->policy = nft_trans_chain_policy(trans);
		break;
	}
}