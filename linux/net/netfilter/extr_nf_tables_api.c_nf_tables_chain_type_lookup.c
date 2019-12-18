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
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct nft_chain_type {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOENT ; 
 struct nft_chain_type const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nft_chain_type* __nf_tables_chain_type_lookup (struct nlattr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_nfnl_nft_mutex_not_held () ; 
 int /*<<< orphan*/  nft_request_module (struct net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 

__attribute__((used)) static const struct nft_chain_type *
nf_tables_chain_type_lookup(struct net *net, const struct nlattr *nla,
			    u8 family, bool autoload)
{
	const struct nft_chain_type *type;

	type = __nf_tables_chain_type_lookup(nla, family);
	if (type != NULL)
		return type;

	lockdep_nfnl_nft_mutex_not_held();
#ifdef CONFIG_MODULES
	if (autoload) {
		nft_request_module(net, "nft-chain-%u-%.*s", family,
				   nla_len(nla), (const char *)nla_data(nla));
		type = __nf_tables_chain_type_lookup(nla, family);
		if (type != NULL)
			return ERR_PTR(-EAGAIN);
	}
#endif
	return ERR_PTR(-ENOENT);
}