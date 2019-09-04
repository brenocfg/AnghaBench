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
typedef  size_t u8 ;
struct nlattr {int dummy; } ;
struct nft_chain_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NFT_CHAIN_T_MAX ; 
 struct nft_chain_type const*** chain_type ; 
 int /*<<< orphan*/  nla_strcmp (struct nlattr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_chain_type *
__nf_tables_chain_type_lookup(const struct nlattr *nla, u8 family)
{
	int i;

	for (i = 0; i < NFT_CHAIN_T_MAX; i++) {
		if (chain_type[family][i] != NULL &&
		    !nla_strcmp(nla, chain_type[family][i]->name))
			return chain_type[family][i];
	}
	return NULL;
}