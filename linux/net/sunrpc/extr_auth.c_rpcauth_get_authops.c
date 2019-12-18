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
struct rpc_authops {int /*<<< orphan*/  owner; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 size_t RPC_AUTH_MAXFLAVOR ; 
 int /*<<< orphan*/ * auth_flavors ; 
 struct rpc_authops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct rpc_authops *
rpcauth_get_authops(rpc_authflavor_t flavor)
{
	const struct rpc_authops *ops;

	if (flavor >= RPC_AUTH_MAXFLAVOR)
		return NULL;

	rcu_read_lock();
	ops = rcu_dereference(auth_flavors[flavor]);
	if (ops == NULL) {
		rcu_read_unlock();
		request_module("rpc-auth-%u", flavor);
		rcu_read_lock();
		ops = rcu_dereference(auth_flavors[flavor]);
		if (ops == NULL)
			goto out;
	}
	if (!try_module_get(ops->owner))
		ops = NULL;
out:
	rcu_read_unlock();
	return ops;
}