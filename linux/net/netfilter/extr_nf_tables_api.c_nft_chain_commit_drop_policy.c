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
struct TYPE_2__ {int /*<<< orphan*/  chain; } ;
struct nft_trans {TYPE_1__ ctx; } ;
struct nft_base_chain {scalar_t__ policy; } ;

/* Variables and functions */
 scalar_t__ NF_DROP ; 
 struct nft_base_chain* nft_base_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_is_base_chain (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_trans_chain_policy (struct nft_trans*) ; 

__attribute__((used)) static void nft_chain_commit_drop_policy(struct nft_trans *trans)
{
	struct nft_base_chain *basechain;

	if (nft_trans_chain_policy(trans) != NF_DROP)
		return;

	if (!nft_is_base_chain(trans->ctx.chain))
		return;

	basechain = nft_base_chain(trans->ctx.chain);
	basechain->policy = NF_DROP;
}