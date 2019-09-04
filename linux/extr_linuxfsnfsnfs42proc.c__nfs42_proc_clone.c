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
struct rpc_message {struct nfs42_clone_res* rpc_resp; struct nfs42_clone_args* rpc_argp; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  cache_consistency_bitmask; } ;
struct nfs_lock_context {int /*<<< orphan*/  open_context; } ;
struct nfs42_clone_res {int /*<<< orphan*/  dst_fattr; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs42_clone_args {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  dst_stateid; int /*<<< orphan*/  src_stateid; int /*<<< orphan*/  dst_bitmask; int /*<<< orphan*/  count; int /*<<< orphan*/  dst_offset; int /*<<< orphan*/  src_offset; int /*<<< orphan*/  dst_fh; int /*<<< orphan*/  src_fh; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfs4_set_rw_stateid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfs_lock_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_alloc_fattr () ; 
 int nfs_post_op_update_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _nfs42_proc_clone(struct rpc_message *msg, struct file *src_f,
		struct file *dst_f, struct nfs_lock_context *src_lock,
		struct nfs_lock_context *dst_lock, loff_t src_offset,
		loff_t dst_offset, loff_t count)
{
	struct inode *src_inode = file_inode(src_f);
	struct inode *dst_inode = file_inode(dst_f);
	struct nfs_server *server = NFS_SERVER(dst_inode);
	struct nfs42_clone_args args = {
		.src_fh = NFS_FH(src_inode),
		.dst_fh = NFS_FH(dst_inode),
		.src_offset = src_offset,
		.dst_offset = dst_offset,
		.count = count,
		.dst_bitmask = server->cache_consistency_bitmask,
	};
	struct nfs42_clone_res res = {
		.server	= server,
	};
	int status;

	msg->rpc_argp = &args;
	msg->rpc_resp = &res;

	status = nfs4_set_rw_stateid(&args.src_stateid, src_lock->open_context,
			src_lock, FMODE_READ);
	if (status)
		return status;

	status = nfs4_set_rw_stateid(&args.dst_stateid, dst_lock->open_context,
			dst_lock, FMODE_WRITE);
	if (status)
		return status;

	res.dst_fattr = nfs_alloc_fattr();
	if (!res.dst_fattr)
		return -ENOMEM;

	status = nfs4_call_sync(server->client, server, msg,
				&args.seq_args, &res.seq_res, 0);
	if (status == 0)
		status = nfs_post_op_update_inode(dst_inode, res.dst_fattr);

	kfree(res.dst_fattr);
	return status;
}