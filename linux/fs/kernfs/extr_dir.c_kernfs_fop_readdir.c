#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ino; } ;
struct kernfs_node {char* name; int /*<<< orphan*/  hash; TYPE_2__ id; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {struct kernfs_node* private_data; TYPE_1__ f_path; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_6__ {void* ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 unsigned int dt_type (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_dentry_node (struct dentry*) ; 
 struct kernfs_node* kernfs_dir_next_pos (void const*,struct kernfs_node*,int /*<<< orphan*/ ,struct kernfs_node*) ; 
 struct kernfs_node* kernfs_dir_pos (void const*,struct kernfs_node*,int /*<<< orphan*/ ,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 TYPE_3__* kernfs_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 scalar_t__ kernfs_ns_enabled (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int kernfs_fop_readdir(struct file *file, struct dir_context *ctx)
{
	struct dentry *dentry = file->f_path.dentry;
	struct kernfs_node *parent = kernfs_dentry_node(dentry);
	struct kernfs_node *pos = file->private_data;
	const void *ns = NULL;

	if (!dir_emit_dots(file, ctx))
		return 0;
	mutex_lock(&kernfs_mutex);

	if (kernfs_ns_enabled(parent))
		ns = kernfs_info(dentry->d_sb)->ns;

	for (pos = kernfs_dir_pos(ns, parent, ctx->pos, pos);
	     pos;
	     pos = kernfs_dir_next_pos(ns, parent, ctx->pos, pos)) {
		const char *name = pos->name;
		unsigned int type = dt_type(pos);
		int len = strlen(name);
		ino_t ino = pos->id.ino;

		ctx->pos = pos->hash;
		file->private_data = pos;
		kernfs_get(pos);

		mutex_unlock(&kernfs_mutex);
		if (!dir_emit(ctx, name, len, ino, type))
			return 0;
		mutex_lock(&kernfs_mutex);
	}
	mutex_unlock(&kernfs_mutex);
	file->private_data = NULL;
	ctx->pos = INT_MAX;
	return 0;
}