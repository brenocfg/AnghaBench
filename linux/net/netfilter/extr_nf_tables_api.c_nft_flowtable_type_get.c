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
struct nf_flowtable_type {int /*<<< orphan*/  owner; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOENT ; 
 struct nf_flowtable_type const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nf_flowtable_type* __nft_flowtable_type_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_nfnl_nft_mutex_not_held () ; 
 int /*<<< orphan*/  nft_request_module (struct net*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nf_flowtable_type *
nft_flowtable_type_get(struct net *net, u8 family)
{
	const struct nf_flowtable_type *type;

	type = __nft_flowtable_type_get(family);
	if (type != NULL && try_module_get(type->owner))
		return type;

	lockdep_nfnl_nft_mutex_not_held();
#ifdef CONFIG_MODULES
	if (type == NULL) {
		nft_request_module(net, "nf-flowtable-%u", family);
		if (__nft_flowtable_type_get(family))
			return ERR_PTR(-EAGAIN);
	}
#endif
	return ERR_PTR(-ENOENT);
}