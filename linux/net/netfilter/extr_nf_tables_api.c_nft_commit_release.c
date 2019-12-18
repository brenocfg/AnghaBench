#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  net; } ;
struct nft_trans {int msg_type; TYPE_2__ ctx; scalar_t__ put_net; } ;
struct TYPE_7__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
#define  NFT_MSG_DELCHAIN 135 
#define  NFT_MSG_DELFLOWTABLE 134 
#define  NFT_MSG_DELOBJ 133 
#define  NFT_MSG_DELRULE 132 
#define  NFT_MSG_DELSET 131 
#define  NFT_MSG_DELSETELEM 130 
#define  NFT_MSG_DELTABLE 129 
#define  NFT_MSG_NEWCHAIN 128 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nft_trans*) ; 
 int /*<<< orphan*/  nf_tables_chain_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  nf_tables_flowtable_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tables_rule_destroy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tables_set_elem_destroy (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tables_table_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  nft_obj_destroy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_destroy (int /*<<< orphan*/ ) ; 
 struct nft_trans* nft_trans_chain_name (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_chain_stats (struct nft_trans*) ; 
 TYPE_1__ nft_trans_elem (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_elem_set (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_flowtable (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_obj (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_rule (struct nft_trans*) ; 
 int /*<<< orphan*/  nft_trans_set (struct nft_trans*) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_commit_release(struct nft_trans *trans)
{
	switch (trans->msg_type) {
	case NFT_MSG_DELTABLE:
		nf_tables_table_destroy(&trans->ctx);
		break;
	case NFT_MSG_NEWCHAIN:
		free_percpu(nft_trans_chain_stats(trans));
		kfree(nft_trans_chain_name(trans));
		break;
	case NFT_MSG_DELCHAIN:
		nf_tables_chain_destroy(&trans->ctx);
		break;
	case NFT_MSG_DELRULE:
		nf_tables_rule_destroy(&trans->ctx, nft_trans_rule(trans));
		break;
	case NFT_MSG_DELSET:
		nft_set_destroy(nft_trans_set(trans));
		break;
	case NFT_MSG_DELSETELEM:
		nf_tables_set_elem_destroy(&trans->ctx,
					   nft_trans_elem_set(trans),
					   nft_trans_elem(trans).priv);
		break;
	case NFT_MSG_DELOBJ:
		nft_obj_destroy(&trans->ctx, nft_trans_obj(trans));
		break;
	case NFT_MSG_DELFLOWTABLE:
		nf_tables_flowtable_destroy(nft_trans_flowtable(trans));
		break;
	}

	if (trans->put_net)
		put_net(trans->ctx.net);

	kfree(trans);
}