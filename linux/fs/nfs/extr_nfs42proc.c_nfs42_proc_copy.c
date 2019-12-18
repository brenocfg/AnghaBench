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
struct nfs_server {int dummy; } ;
struct nfs_lock_context {TYPE_1__* open_context; } ;
struct nfs4_exception {int retry; int /*<<< orphan*/  state; int /*<<< orphan*/ * stateid; int /*<<< orphan*/  inode; } ;
struct nfs42_copy_res {int dummy; } ;
struct nfs42_copy_args {size_t count; int sync; int /*<<< orphan*/  dst_stateid; int /*<<< orphan*/  src_stateid; int /*<<< orphan*/  dst_pos; int /*<<< orphan*/  dst_fh; int /*<<< orphan*/  src_pos; int /*<<< orphan*/  src_fh; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  NFS4ERR_OFFLOAD_NO_REQS ; 
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  _nfs42_proc_copy (struct file*,struct nfs_lock_context*,struct file*,struct nfs_lock_context*,struct nfs42_copy_args*,struct nfs42_copy_res*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_handle_exception (struct nfs_server*,int /*<<< orphan*/ ,struct nfs4_exception*) ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 struct nfs_lock_context* nfs_get_lock_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 

ssize_t nfs42_proc_copy(struct file *src, loff_t pos_src,
			struct file *dst, loff_t pos_dst,
			size_t count)
{
	struct nfs_server *server = NFS_SERVER(file_inode(dst));
	struct nfs_lock_context *src_lock;
	struct nfs_lock_context *dst_lock;
	struct nfs42_copy_args args = {
		.src_fh		= NFS_FH(file_inode(src)),
		.src_pos	= pos_src,
		.dst_fh		= NFS_FH(file_inode(dst)),
		.dst_pos	= pos_dst,
		.count		= count,
		.sync		= false,
	};
	struct nfs42_copy_res res;
	struct nfs4_exception src_exception = {
		.inode		= file_inode(src),
		.stateid	= &args.src_stateid,
	};
	struct nfs4_exception dst_exception = {
		.inode		= file_inode(dst),
		.stateid	= &args.dst_stateid,
	};
	ssize_t err, err2;

	src_lock = nfs_get_lock_context(nfs_file_open_context(src));
	if (IS_ERR(src_lock))
		return PTR_ERR(src_lock);

	src_exception.state = src_lock->open_context->state;

	dst_lock = nfs_get_lock_context(nfs_file_open_context(dst));
	if (IS_ERR(dst_lock)) {
		err = PTR_ERR(dst_lock);
		goto out_put_src_lock;
	}

	dst_exception.state = dst_lock->open_context->state;

	do {
		inode_lock(file_inode(dst));
		err = _nfs42_proc_copy(src, src_lock,
				dst, dst_lock,
				&args, &res);
		inode_unlock(file_inode(dst));

		if (err >= 0)
			break;
		if (err == -ENOTSUPP) {
			err = -EOPNOTSUPP;
			break;
		} else if (err == -EAGAIN) {
			dst_exception.retry = 1;
			continue;
		} else if (err == -NFS4ERR_OFFLOAD_NO_REQS && !args.sync) {
			args.sync = true;
			dst_exception.retry = 1;
			continue;
		}

		err2 = nfs4_handle_exception(server, err, &src_exception);
		err  = nfs4_handle_exception(server, err, &dst_exception);
		if (!err)
			err = err2;
	} while (src_exception.retry || dst_exception.retry);

	nfs_put_lock_context(dst_lock);
out_put_src_lock:
	nfs_put_lock_context(src_lock);
	return err;
}