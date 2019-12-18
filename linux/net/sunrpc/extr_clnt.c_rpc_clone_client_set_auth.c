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
struct rpc_create_args {int /*<<< orphan*/  cred; int /*<<< orphan*/  authflavor; int /*<<< orphan*/  version; int /*<<< orphan*/  prognumber; int /*<<< orphan*/  program; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_cred; int /*<<< orphan*/  cl_vers; int /*<<< orphan*/  cl_prog; int /*<<< orphan*/  cl_program; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 struct rpc_clnt* __rpc_clone_client (struct rpc_create_args*,struct rpc_clnt*) ; 

struct rpc_clnt *
rpc_clone_client_set_auth(struct rpc_clnt *clnt, rpc_authflavor_t flavor)
{
	struct rpc_create_args args = {
		.program	= clnt->cl_program,
		.prognumber	= clnt->cl_prog,
		.version	= clnt->cl_vers,
		.authflavor	= flavor,
		.cred		= clnt->cl_cred,
	};
	return __rpc_clone_client(&args, clnt);
}