#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {struct dentry* private_data; TYPE_1__ f_path; } ;
struct dir_context {int pos; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {struct list_head d_child; TYPE_2__ d_name; struct list_head d_subdirs; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_3__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  dt_type (TYPE_3__*) ; 
 int /*<<< orphan*/  move_cursor (struct dentry*,struct list_head*) ; 
 struct dentry* next_positive (struct dentry*,struct list_head*,int) ; 

int dcache_readdir(struct file *file, struct dir_context *ctx)
{
	struct dentry *dentry = file->f_path.dentry;
	struct dentry *cursor = file->private_data;
	struct list_head *p = &cursor->d_child;
	struct dentry *next;
	bool moved = false;

	if (!dir_emit_dots(file, ctx))
		return 0;

	if (ctx->pos == 2)
		p = &dentry->d_subdirs;
	while ((next = next_positive(dentry, p, 1)) != NULL) {
		if (!dir_emit(ctx, next->d_name.name, next->d_name.len,
			      d_inode(next)->i_ino, dt_type(d_inode(next))))
			break;
		moved = true;
		p = &next->d_child;
		ctx->pos++;
	}
	if (moved)
		move_cursor(cursor, p);
	return 0;
}