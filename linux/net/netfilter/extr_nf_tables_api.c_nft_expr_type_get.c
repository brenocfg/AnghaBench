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
struct nft_expr_type {int /*<<< orphan*/  owner; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct nft_expr_type const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nft_expr_type* __nft_expr_type_get (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  lockdep_nfnl_nft_mutex_not_held () ; 
 int /*<<< orphan*/  nft_expr_type_request_module (struct net*,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nft_request_module (struct net*,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_type *nft_expr_type_get(struct net *net,
						     u8 family,
						     struct nlattr *nla)
{
	const struct nft_expr_type *type;

	if (nla == NULL)
		return ERR_PTR(-EINVAL);

	type = __nft_expr_type_get(family, nla);
	if (type != NULL && try_module_get(type->owner))
		return type;

	lockdep_nfnl_nft_mutex_not_held();
#ifdef CONFIG_MODULES
	if (type == NULL) {
		if (nft_expr_type_request_module(net, family, nla) == -EAGAIN)
			return ERR_PTR(-EAGAIN);

		nft_request_module(net, "nft-expr-%.*s",
				   nla_len(nla), (char *)nla_data(nla));
		if (__nft_expr_type_get(family, nla))
			return ERR_PTR(-EAGAIN);
	}
#endif
	return ERR_PTR(-ENOENT);
}