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
struct nft_table {int dummy; } ;
struct nft_set {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nft_set*) ; 
 struct nft_set* nft_set_lookup (struct nft_table const*,struct nlattr const*,int /*<<< orphan*/ ) ; 
 struct nft_set* nft_set_lookup_byid (struct net const*,struct nlattr const*,int /*<<< orphan*/ ) ; 

struct nft_set *nft_set_lookup_global(const struct net *net,
				      const struct nft_table *table,
				      const struct nlattr *nla_set_name,
				      const struct nlattr *nla_set_id,
				      u8 genmask)
{
	struct nft_set *set;

	set = nft_set_lookup(table, nla_set_name, genmask);
	if (IS_ERR(set)) {
		if (!nla_set_id)
			return set;

		set = nft_set_lookup_byid(net, nla_set_id, genmask);
	}
	return set;
}