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
struct nlattr {int dummy; } ;
struct nft_rule {int dummy; } ;
struct nft_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nft_rule* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nft_rule* __nft_rule_lookup (struct nft_chain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be64 (struct nlattr const*) ; 

__attribute__((used)) static struct nft_rule *nft_rule_lookup(const struct nft_chain *chain,
					const struct nlattr *nla)
{
	if (nla == NULL)
		return ERR_PTR(-EINVAL);

	return __nft_rule_lookup(chain, be64_to_cpu(nla_get_be64(nla)));
}