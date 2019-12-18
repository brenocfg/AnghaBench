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
struct inode {int /*<<< orphan*/  i_rwsem; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_1__* f_op; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
struct TYPE_2__ {int (* iterate_shared ) (struct file*,struct dir_context*) ;int (* iterate ) (struct file*,struct dir_context*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  IS_DEADDIR (struct inode*) ; 
 int /*<<< orphan*/  MAY_READ ; 
 int down_read_killable (int /*<<< orphan*/ *) ; 
 int down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fsnotify_access (struct file*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 int security_file_permission (struct file*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,struct dir_context*) ; 
 int stub2 (struct file*,struct dir_context*) ; 

int iterate_dir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	bool shared = false;
	int res = -ENOTDIR;
	if (file->f_op->iterate_shared)
		shared = true;
	else if (!file->f_op->iterate)
		goto out;

	res = security_file_permission(file, MAY_READ);
	if (res)
		goto out;

	if (shared)
		res = down_read_killable(&inode->i_rwsem);
	else
		res = down_write_killable(&inode->i_rwsem);
	if (res)
		goto out;

	res = -ENOENT;
	if (!IS_DEADDIR(inode)) {
		ctx->pos = file->f_pos;
		if (shared)
			res = file->f_op->iterate_shared(file, ctx);
		else
			res = file->f_op->iterate(file, ctx);
		file->f_pos = ctx->pos;
		fsnotify_access(file);
		file_accessed(file);
	}
	if (shared)
		inode_unlock_shared(inode);
	else
		inode_unlock(inode);
out:
	return res;
}