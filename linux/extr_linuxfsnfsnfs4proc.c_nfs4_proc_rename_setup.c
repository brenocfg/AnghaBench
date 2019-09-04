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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct nfs_renameres* rpc_resp; struct nfs_renameargs* rpc_argp; } ;
struct nfs_renameres {int /*<<< orphan*/  seq_res; int /*<<< orphan*/  server; } ;
struct nfs_renameargs {int /*<<< orphan*/  seq_args; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_RENAME ; 
 int /*<<< orphan*/  NFS_SB (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_inode_make_writeable (struct inode*) ; 
 int /*<<< orphan*/  nfs4_inode_return_delegation (struct inode*) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static void nfs4_proc_rename_setup(struct rpc_message *msg,
		struct dentry *old_dentry,
		struct dentry *new_dentry)
{
	struct nfs_renameargs *arg = msg->rpc_argp;
	struct nfs_renameres *res = msg->rpc_resp;
	struct inode *old_inode = d_inode(old_dentry);
	struct inode *new_inode = d_inode(new_dentry);

	if (old_inode)
		nfs4_inode_make_writeable(old_inode);
	if (new_inode)
		nfs4_inode_return_delegation(new_inode);
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RENAME];
	res->server = NFS_SB(old_dentry->d_sb);
	nfs4_init_sequence(&arg->seq_args, &res->seq_res, 1, 0);
}