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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_clnt {struct rpc_auth* cl_auth; } ;
struct rpc_authops {struct rpc_auth* (* create ) (struct rpc_auth_create_args const*,struct rpc_clnt*) ;} ;
struct rpc_auth_create_args {int /*<<< orphan*/  pseudoflavor; } ;
struct rpc_auth {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rpc_auth* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rpc_auth*) ; 
 int /*<<< orphan*/  pseudoflavor_to_flavor (int /*<<< orphan*/ ) ; 
 struct rpc_authops* rpcauth_get_authops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcauth_put_authops (struct rpc_authops const*) ; 
 int /*<<< orphan*/  rpcauth_release (struct rpc_auth*) ; 
 struct rpc_auth* stub1 (struct rpc_auth_create_args const*,struct rpc_clnt*) ; 

struct rpc_auth *
rpcauth_create(const struct rpc_auth_create_args *args, struct rpc_clnt *clnt)
{
	struct rpc_auth	*auth = ERR_PTR(-EINVAL);
	const struct rpc_authops *ops;
	u32 flavor = pseudoflavor_to_flavor(args->pseudoflavor);

	ops = rpcauth_get_authops(flavor);
	if (ops == NULL)
		goto out;

	auth = ops->create(args, clnt);

	rpcauth_put_authops(ops);
	if (IS_ERR(auth))
		return auth;
	if (clnt->cl_auth)
		rpcauth_release(clnt->cl_auth);
	clnt->cl_auth = auth;

out:
	return auth;
}