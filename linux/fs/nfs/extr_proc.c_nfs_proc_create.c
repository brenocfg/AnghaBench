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
struct rpc_message {TYPE_1__* rpc_resp; int /*<<< orphan*/ * rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct TYPE_2__ {int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; } ;
struct nfs_createdata {TYPE_1__ res; int /*<<< orphan*/  arg; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFSPROC_CREATE ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 struct nfs_createdata* nfs_alloc_createdata (struct inode*,struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  nfs_free_createdata (struct nfs_createdata*) ; 
 int nfs_instantiate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_create(struct inode *dir, struct dentry *dentry, struct iattr *sattr,
		int flags)
{
	struct nfs_createdata *data;
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_CREATE],
	};
	int status = -ENOMEM;

	dprintk("NFS call  create %pd\n", dentry);
	data = nfs_alloc_createdata(dir, dentry, sattr);
	if (data == NULL)
		goto out;
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_for_revalidate(dir);
	if (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, NULL);
	nfs_free_createdata(data);
out:
	dprintk("NFS reply create: %d\n", status);
	return status;
}