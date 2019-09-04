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
struct nft_table {int flags; } ;
struct nft_chain {int dummy; } ;
struct nf_hook_ops {int dummy; } ;
struct nft_base_chain {TYPE_1__* type; struct nf_hook_ops ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int (* ops_register ) (struct net*,struct nf_hook_ops const*) ;} ;

/* Variables and functions */
 int NFT_TABLE_F_DORMANT ; 
 int nf_register_net_hook (struct net*,struct nf_hook_ops const*) ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain*) ; 
 int /*<<< orphan*/  nft_is_base_chain (struct nft_chain*) ; 
 int stub1 (struct net*,struct nf_hook_ops const*) ; 

__attribute__((used)) static int nf_tables_register_hook(struct net *net,
				   const struct nft_table *table,
				   struct nft_chain *chain)
{
	const struct nft_base_chain *basechain;
	const struct nf_hook_ops *ops;

	if (table->flags & NFT_TABLE_F_DORMANT ||
	    !nft_is_base_chain(chain))
		return 0;

	basechain = nft_base_chain(chain);
	ops = &basechain->ops;

	if (basechain->type->ops_register)
		return basechain->type->ops_register(net, ops);

	return nf_register_net_hook(net, ops);
}