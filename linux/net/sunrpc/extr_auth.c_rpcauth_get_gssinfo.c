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
struct rpc_authops {int (* flavor2info ) (int /*<<< orphan*/ ,struct rpcsec_gss_info*) ;} ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  pseudoflavor_to_flavor (int /*<<< orphan*/ ) ; 
 struct rpc_authops* rpcauth_get_authops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcauth_put_authops (struct rpc_authops const*) ; 
 int stub1 (int /*<<< orphan*/ ,struct rpcsec_gss_info*) ; 

int
rpcauth_get_gssinfo(rpc_authflavor_t pseudoflavor, struct rpcsec_gss_info *info)
{
	rpc_authflavor_t flavor = pseudoflavor_to_flavor(pseudoflavor);
	const struct rpc_authops *ops;
	int result;

	ops = rpcauth_get_authops(flavor);
	if (ops == NULL)
		return -ENOENT;

	result = -ENOENT;
	if (ops->flavor2info != NULL)
		result = ops->flavor2info(pseudoflavor, info);

	rpcauth_put_authops(ops);
	return result;
}