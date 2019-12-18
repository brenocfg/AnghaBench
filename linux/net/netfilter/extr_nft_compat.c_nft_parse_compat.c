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
typedef  int u32 ;
typedef  void* u16 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_RULE_COMPAT_FLAGS ; 
 int /*<<< orphan*/  NFTA_RULE_COMPAT_MAX ; 
 size_t NFTA_RULE_COMPAT_PROTO ; 
 int NFT_RULE_COMPAT_F_INV ; 
 int NFT_RULE_COMPAT_F_MASK ; 
 int /*<<< orphan*/  nft_rule_compat_policy ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_parse_compat(const struct nlattr *attr, u16 *proto, bool *inv)
{
	struct nlattr *tb[NFTA_RULE_COMPAT_MAX+1];
	u32 flags;
	int err;

	err = nla_parse_nested_deprecated(tb, NFTA_RULE_COMPAT_MAX, attr,
					  nft_rule_compat_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[NFTA_RULE_COMPAT_PROTO] || !tb[NFTA_RULE_COMPAT_FLAGS])
		return -EINVAL;

	flags = ntohl(nla_get_be32(tb[NFTA_RULE_COMPAT_FLAGS]));
	if (flags & ~NFT_RULE_COMPAT_F_MASK)
		return -EINVAL;
	if (flags & NFT_RULE_COMPAT_F_INV)
		*inv = true;

	*proto = ntohl(nla_get_be32(tb[NFTA_RULE_COMPAT_PROTO]));
	return 0;
}