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
struct rpc_task {TYPE_1__* tk_client; } ;
struct rpc_cred {int dummy; } ;
struct rpc_auth {int dummy; } ;
struct TYPE_2__ {struct rpc_auth* cl_auth; } ;

/* Variables and functions */
 struct rpc_cred* rpcauth_lookupcred (struct rpc_auth*,int) ; 

__attribute__((used)) static struct rpc_cred *
rpcauth_bind_new_cred(struct rpc_task *task, int lookupflags)
{
	struct rpc_auth *auth = task->tk_client->cl_auth;

	return rpcauth_lookupcred(auth, lookupflags);
}