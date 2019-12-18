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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct mountres* rpc_resp; int /*<<< orphan*/  rpc_argp; } ;
struct rpc_create_args {char* servername; scalar_t__ version; int /*<<< orphan*/  flags; int /*<<< orphan*/  cred; int /*<<< orphan*/  authflavor; int /*<<< orphan*/ * program; int /*<<< orphan*/  addrsize; int /*<<< orphan*/  address; int /*<<< orphan*/  protocol; int /*<<< orphan*/  net; } ;
struct rpc_clnt {int /*<<< orphan*/ * cl_procinfo; } ;
struct nfs_mount_request {int* auth_flav_len; char* hostname; scalar_t__ version; int /*<<< orphan*/ * auth_flavs; scalar_t__ noresvport; int /*<<< orphan*/  dirpath; int /*<<< orphan*/  salen; int /*<<< orphan*/  sap; int /*<<< orphan*/  protocol; int /*<<< orphan*/  net; int /*<<< orphan*/  fh; } ;
struct mountres {int* auth_count; int errno; int /*<<< orphan*/ * auth_flavors; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 scalar_t__ MNTPATHLEN ; 
 size_t MOUNTPROC3_MNT ; 
 size_t MOUNTPROC_MNT ; 
 scalar_t__ NFS_MNT3_VERSION ; 
 int PTR_ERR (struct rpc_clnt*) ; 
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int /*<<< orphan*/  RPC_CLNT_CREATE_NONPRIVPORT ; 
 int RPC_TASK_SOFT ; 
 int RPC_TASK_TIMEOUT ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  mnt_program ; 
 int rpc_call_sync (struct rpc_clnt*,struct rpc_message*,int) ; 
 struct rpc_clnt* rpc_create (struct rpc_create_args*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int nfs_mount(struct nfs_mount_request *info)
{
	struct mountres	result = {
		.fh		= info->fh,
		.auth_count	= info->auth_flav_len,
		.auth_flavors	= info->auth_flavs,
	};
	struct rpc_message msg	= {
		.rpc_argp	= info->dirpath,
		.rpc_resp	= &result,
	};
	struct rpc_create_args args = {
		.net		= info->net,
		.protocol	= info->protocol,
		.address	= info->sap,
		.addrsize	= info->salen,
		.servername	= info->hostname,
		.program	= &mnt_program,
		.version	= info->version,
		.authflavor	= RPC_AUTH_UNIX,
		.cred		= current_cred(),
	};
	struct rpc_clnt		*mnt_clnt;
	int			status;

	dprintk("NFS: sending MNT request for %s:%s\n",
		(info->hostname ? info->hostname : "server"),
			info->dirpath);

	if (strlen(info->dirpath) > MNTPATHLEN)
		return -ENAMETOOLONG;

	if (info->noresvport)
		args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;

	mnt_clnt = rpc_create(&args);
	if (IS_ERR(mnt_clnt))
		goto out_clnt_err;

	if (info->version == NFS_MNT3_VERSION)
		msg.rpc_proc = &mnt_clnt->cl_procinfo[MOUNTPROC3_MNT];
	else
		msg.rpc_proc = &mnt_clnt->cl_procinfo[MOUNTPROC_MNT];

	status = rpc_call_sync(mnt_clnt, &msg, RPC_TASK_SOFT|RPC_TASK_TIMEOUT);
	rpc_shutdown_client(mnt_clnt);

	if (status < 0)
		goto out_call_err;
	if (result.errno != 0)
		goto out_mnt_err;

	dprintk("NFS: MNT request succeeded\n");
	status = 0;

	/*
	 * If the server didn't provide a flavor list, allow the
	 * client to try any flavor.
	 */
	if (info->version != NFS_MNT3_VERSION || *info->auth_flav_len == 0) {
		dprintk("NFS: Faking up auth_flavs list\n");
		info->auth_flavs[0] = RPC_AUTH_NULL;
		*info->auth_flav_len = 1;
	}
out:
	return status;

out_clnt_err:
	status = PTR_ERR(mnt_clnt);
	dprintk("NFS: failed to create MNT RPC client, status=%d\n", status);
	goto out;

out_call_err:
	dprintk("NFS: MNT request failed, status=%d\n", status);
	goto out;

out_mnt_err:
	dprintk("NFS: MNT server returned result %d\n", result.errno);
	status = result.errno;
	goto out;
}