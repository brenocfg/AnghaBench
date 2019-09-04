#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {TYPE_2__* cr_auth; } ;
struct rpc_auth {int dummy; } ;
struct TYPE_4__ {TYPE_1__* au_ops; } ;
struct TYPE_3__ {int (* key_timeout ) (struct rpc_auth*,struct rpc_cred*) ;} ;

/* Variables and functions */
 int stub1 (struct rpc_auth*,struct rpc_cred*) ; 

int
rpcauth_key_timeout_notify(struct rpc_auth *auth, struct rpc_cred *cred)
{
	if (!cred->cr_auth->au_ops->key_timeout)
		return 0;
	return cred->cr_auth->au_ops->key_timeout(auth, cred);
}