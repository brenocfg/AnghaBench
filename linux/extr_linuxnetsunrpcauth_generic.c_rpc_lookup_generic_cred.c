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
struct rpc_cred {int dummy; } ;
struct auth_cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  generic_auth ; 
 struct rpc_cred* rpcauth_lookup_credcache (int /*<<< orphan*/ *,struct auth_cred*,int,int /*<<< orphan*/ ) ; 

struct rpc_cred *
rpc_lookup_generic_cred(struct auth_cred *acred, int flags, gfp_t gfp)
{
	return rpcauth_lookup_credcache(&generic_auth, acred, flags, gfp);
}