#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {TYPE_1__* cr_ops; } ;
struct rpc_auth {int au_flags; } ;
struct TYPE_2__ {int (* crkey_to_expire ) (struct rpc_cred*) ;} ;

/* Variables and functions */
 int RPCAUTH_AUTH_NO_CRKEY_TIMEOUT ; 
 int stub1 (struct rpc_cred*) ; 

bool
rpcauth_cred_key_to_expire(struct rpc_auth *auth, struct rpc_cred *cred)
{
	if (auth->au_flags & RPCAUTH_AUTH_NO_CRKEY_TIMEOUT)
		return false;
	if (!cred->cr_ops->crkey_to_expire)
		return false;
	return cred->cr_ops->crkey_to_expire(cred);
}