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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_program {int /*<<< orphan*/  number; } ;
struct rpc_create_args {int /*<<< orphan*/  cred; int /*<<< orphan*/  authflavor; int /*<<< orphan*/  version; int /*<<< orphan*/  prognumber; struct rpc_program const* program; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_cred; TYPE_1__* cl_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/  au_flavor; } ;

/* Variables and functions */
 struct rpc_clnt* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 struct rpc_clnt* __rpc_clone_client (struct rpc_create_args*,struct rpc_clnt*) ; 
 int rpc_ping (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

struct rpc_clnt *rpc_bind_new_program(struct rpc_clnt *old,
				      const struct rpc_program *program,
				      u32 vers)
{
	struct rpc_create_args args = {
		.program	= program,
		.prognumber	= program->number,
		.version	= vers,
		.authflavor	= old->cl_auth->au_flavor,
		.cred		= old->cl_cred,
	};
	struct rpc_clnt *clnt;
	int err;

	clnt = __rpc_clone_client(&args, old);
	if (IS_ERR(clnt))
		goto out;
	err = rpc_ping(clnt);
	if (err != 0) {
		rpc_shutdown_client(clnt);
		clnt = ERR_PTR(err);
	}
out:
	return clnt;
}