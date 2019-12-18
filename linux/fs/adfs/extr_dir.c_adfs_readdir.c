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
struct super_block {int dummy; } ;
struct object_info {char* name; int name_len; int /*<<< orphan*/  indaddr; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;
struct adfs_dir_ops {int (* read ) (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adfs_dir*) ;int (* setpos ) (struct adfs_dir*,int) ;scalar_t__ (* getnext ) (struct adfs_dir*,struct object_info*) ;int /*<<< orphan*/  (* free ) (struct adfs_dir*) ;} ;
struct adfs_dir {int /*<<< orphan*/  parent_id; } ;
struct TYPE_2__ {struct adfs_dir_ops* s_dir; } ;

/* Variables and functions */
 TYPE_1__* ADFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int /*<<< orphan*/  adfs_dir_lock ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit_dot (struct file*,struct dir_context*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adfs_dir*) ; 
 int stub2 (struct adfs_dir*,int) ; 
 scalar_t__ stub3 (struct adfs_dir*,struct object_info*) ; 
 int /*<<< orphan*/  stub4 (struct adfs_dir*) ; 

__attribute__((used)) static int
adfs_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	const struct adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	struct object_info obj;
	struct adfs_dir dir;
	int ret = 0;

	if (ctx->pos >> 32)
		return 0;

	ret = ops->read(sb, inode->i_ino, inode->i_size, &dir);
	if (ret)
		return ret;

	if (ctx->pos == 0) {
		if (!dir_emit_dot(file, ctx))
			goto free_out;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (!dir_emit(ctx, "..", 2, dir.parent_id, DT_DIR))
			goto free_out;
		ctx->pos = 2;
	}

	read_lock(&adfs_dir_lock);

	ret = ops->setpos(&dir, ctx->pos - 2);
	if (ret)
		goto unlock_out;
	while (ops->getnext(&dir, &obj) == 0) {
		if (!dir_emit(ctx, obj.name, obj.name_len,
			      obj.indaddr, DT_UNKNOWN))
			break;
		ctx->pos++;
	}

unlock_out:
	read_unlock(&adfs_dir_lock);

free_out:
	ops->free(&dir);
	return ret;
}