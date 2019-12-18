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
struct rpc_cred {unsigned long cr_flags; } ;
struct rpc_auth {int dummy; } ;
struct auth_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long RPCAUTH_CRED_UPTODATE ; 
 struct rpc_cred* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcauth_init_cred (struct rpc_cred*,struct auth_cred*,struct rpc_auth*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_credops ; 
 int /*<<< orphan*/  unix_pool ; 

__attribute__((used)) static struct rpc_cred *
unx_lookup_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags)
{
	struct rpc_cred *ret = mempool_alloc(unix_pool, GFP_NOFS);

	rpcauth_init_cred(ret, acred, auth, &unix_credops);
	ret->cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;
	return ret;
}