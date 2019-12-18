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
struct nft_chain {int dummy; } ;
struct nft_base_chain {TYPE_1__* type; } ;
typedef  enum nft_chain_types { ____Placeholder_nft_chain_types } nft_chain_types ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain const*) ; 
 scalar_t__ nft_is_base_chain (struct nft_chain const*) ; 

int nft_chain_validate_dependency(const struct nft_chain *chain,
				  enum nft_chain_types type)
{
	const struct nft_base_chain *basechain;

	if (nft_is_base_chain(chain)) {
		basechain = nft_base_chain(chain);
		if (basechain->type->type != type)
			return -EOPNOTSUPP;
	}
	return 0;
}