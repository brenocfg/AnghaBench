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
typedef  scalar_t__ u32 ;
struct rpc_message {struct nfs_removeres* rpc_resp; struct nfs_removeargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_removeres {int /*<<< orphan*/  cinfo; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs_removeargs {int /*<<< orphan*/  seq_args; struct qstr const name; int /*<<< orphan*/  fh; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 scalar_t__ NF4DIR ; 
 size_t NFSPROC4_CLNT_REMOVE ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 unsigned long jiffies ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_dec_nlink_locked (struct inode*) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr_locked (struct inode*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_nfs4_proc_remove(struct inode *dir, const struct qstr *name, u32 ftype)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs_removeargs args = {
		.fh = NFS_FH(dir),
		.name = *name,
	};
	struct nfs_removeres res = {
		.server = server,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVE],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};
	unsigned long timestamp = jiffies;
	int status;

	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 1);
	if (status == 0) {
		spin_lock(&dir->i_lock);
		update_changeattr_locked(dir, &res.cinfo, timestamp, 0);
		/* Removing a directory decrements nlink in the parent */
		if (ftype == NF4DIR && dir->i_nlink > 2)
			nfs4_dec_nlink_locked(dir);
		spin_unlock(&dir->i_lock);
	}
	return status;
}