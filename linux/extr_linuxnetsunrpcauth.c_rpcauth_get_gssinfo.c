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
struct rpc_authops {int (* flavor2info ) (size_t,struct rpcsec_gss_info*) ;int /*<<< orphan*/  owner; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 size_t RPC_AUTH_MAXFLAVOR ; 
 struct rpc_authops** auth_flavors ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 size_t pseudoflavor_to_flavor (size_t) ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int /*<<< orphan*/  rpc_authflavor_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (size_t,struct rpcsec_gss_info*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
rpcauth_get_gssinfo(rpc_authflavor_t pseudoflavor, struct rpcsec_gss_info *info)
{
	rpc_authflavor_t flavor = pseudoflavor_to_flavor(pseudoflavor);
	const struct rpc_authops *ops;
	int result;

	if (flavor >= RPC_AUTH_MAXFLAVOR)
		return -EINVAL;

	ops = auth_flavors[flavor];
	if (ops == NULL)
		request_module("rpc-auth-%u", flavor);
	spin_lock(&rpc_authflavor_lock);
	ops = auth_flavors[flavor];
	if (ops == NULL || !try_module_get(ops->owner)) {
		spin_unlock(&rpc_authflavor_lock);
		return -ENOENT;
	}
	spin_unlock(&rpc_authflavor_lock);

	result = -ENOENT;
	if (ops->flavor2info != NULL)
		result = ops->flavor2info(pseudoflavor, info);

	module_put(ops->owner);
	return result;
}