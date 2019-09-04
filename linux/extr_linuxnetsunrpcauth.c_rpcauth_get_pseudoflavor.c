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
struct rpcsec_gss_info {int dummy; } ;
struct rpc_authops {size_t (* info2flavor ) (struct rpcsec_gss_info*) ;int /*<<< orphan*/  owner; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 size_t RPC_AUTH_MAXFLAVOR ; 
 struct rpc_authops** auth_flavors ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int /*<<< orphan*/  rpc_authflavor_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t stub1 (struct rpcsec_gss_info*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

rpc_authflavor_t
rpcauth_get_pseudoflavor(rpc_authflavor_t flavor, struct rpcsec_gss_info *info)
{
	const struct rpc_authops *ops;
	rpc_authflavor_t pseudoflavor;

	ops = auth_flavors[flavor];
	if (ops == NULL)
		request_module("rpc-auth-%u", flavor);
	spin_lock(&rpc_authflavor_lock);
	ops = auth_flavors[flavor];
	if (ops == NULL || !try_module_get(ops->owner)) {
		spin_unlock(&rpc_authflavor_lock);
		return RPC_AUTH_MAXFLAVOR;
	}
	spin_unlock(&rpc_authflavor_lock);

	pseudoflavor = flavor;
	if (ops->info2flavor != NULL)
		pseudoflavor = ops->info2flavor(info);

	module_put(ops->owner);
	return pseudoflavor;
}