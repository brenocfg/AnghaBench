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
struct TYPE_2__ {int hooknum; } ;
struct nft_base_chain {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain const*) ; 
 scalar_t__ nft_is_base_chain (struct nft_chain const*) ; 

int nft_chain_validate_hooks(const struct nft_chain *chain,
			     unsigned int hook_flags)
{
	struct nft_base_chain *basechain;

	if (nft_is_base_chain(chain)) {
		basechain = nft_base_chain(chain);

		if ((1 << basechain->ops.hooknum) & hook_flags)
			return 0;

		return -EOPNOTSUPP;
	}

	return 0;
}