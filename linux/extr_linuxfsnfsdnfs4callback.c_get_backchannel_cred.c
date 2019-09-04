#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {int dummy; } ;
struct rpc_clnt {struct rpc_auth* cl_auth; } ;
struct rpc_auth {TYPE_2__* au_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct nfsd4_session {TYPE_1__ se_cb_sec; } ;
struct TYPE_6__ {char* cr_targ_princ; } ;
struct nfs4_client {scalar_t__ cl_minorversion; TYPE_3__ cl_cred; } ;
struct auth_cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_5__ {struct rpc_cred* (* lookup_cred ) (struct rpc_auth*,struct auth_cred*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rpc_cred*) ; 
 int /*<<< orphan*/  get_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpc_lookup_machine_cred (char*) ; 
 struct rpc_cred* stub1 (struct rpc_auth*,struct auth_cred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_cred *get_backchannel_cred(struct nfs4_client *clp, struct rpc_clnt *client, struct nfsd4_session *ses)
{
	if (clp->cl_minorversion == 0) {
		char *principal = clp->cl_cred.cr_targ_princ ?
					clp->cl_cred.cr_targ_princ : "nfs";
		struct rpc_cred *cred;

		cred = rpc_lookup_machine_cred(principal);
		if (!IS_ERR(cred))
			get_rpccred(cred);
		return cred;
	} else {
		struct rpc_auth *auth = client->cl_auth;
		struct auth_cred acred = {};

		acred.uid = ses->se_cb_sec.uid;
		acred.gid = ses->se_cb_sec.gid;
		return auth->au_ops->lookup_cred(client->cl_auth, &acred, 0);
	}
}