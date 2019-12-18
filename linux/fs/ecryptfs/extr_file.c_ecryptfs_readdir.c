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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  actor; } ;
struct ecryptfs_getdents_callback {int /*<<< orphan*/  entries_written; scalar_t__ filldir_called; TYPE_1__ ctx; int /*<<< orphan*/  sb; struct dir_context* caller; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 struct file* ecryptfs_file_to_lower (struct file*) ; 
 int /*<<< orphan*/  ecryptfs_filldir ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_atime (struct inode*,struct inode*) ; 
 int iterate_dir (struct file*,TYPE_1__*) ; 

__attribute__((used)) static int ecryptfs_readdir(struct file *file, struct dir_context *ctx)
{
	int rc;
	struct file *lower_file;
	struct inode *inode = file_inode(file);
	struct ecryptfs_getdents_callback buf = {
		.ctx.actor = ecryptfs_filldir,
		.caller = ctx,
		.sb = inode->i_sb,
	};
	lower_file = ecryptfs_file_to_lower(file);
	rc = iterate_dir(lower_file, &buf.ctx);
	ctx->pos = buf.ctx.pos;
	if (rc < 0)
		goto out;
	if (buf.filldir_called && !buf.entries_written)
		goto out;
	if (rc >= 0)
		fsstack_copy_attr_atime(inode,
					file_inode(lower_file));
out:
	return rc;
}