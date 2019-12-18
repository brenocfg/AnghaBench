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
struct dentry {int /*<<< orphan*/  d_lock; struct list_head d_child; TYPE_2__ d_name; struct list_head d_subdirs; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_3__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  dt_type (TYPE_3__*) ; 
 int /*<<< orphan*/  list_del_init (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (struct list_head*,struct list_head*) ; 
 struct dentry* scan_positives (struct dentry*,struct list_head*,int,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dcache_readdir(struct file *file, struct dir_context *ctx)
{
	struct dentry *dentry = file->f_path.dentry;
	struct dentry *cursor = file->private_data;
	struct list_head *anchor = &dentry->d_subdirs;
	struct dentry *next = NULL;
	struct list_head *p;

	if (!dir_emit_dots(file, ctx))
		return 0;

	if (ctx->pos == 2)
		p = anchor;
	else if (!list_empty(&cursor->d_child))
		p = &cursor->d_child;
	else
		return 0;

	while ((next = scan_positives(cursor, p, 1, next)) != NULL) {
		if (!dir_emit(ctx, next->d_name.name, next->d_name.len,
			      d_inode(next)->i_ino, dt_type(d_inode(next))))
			break;
		ctx->pos++;
		p = &next->d_child;
	}
	spin_lock(&dentry->d_lock);
	if (next)
		list_move_tail(&cursor->d_child, &next->d_child);
	else
		list_del_init(&cursor->d_child);
	spin_unlock(&dentry->d_lock);
	dput(next);

	return 0;
}