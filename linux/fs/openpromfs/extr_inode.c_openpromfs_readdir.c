#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct property {char* name; struct property* next; int /*<<< orphan*/  unique_id; } ;
struct TYPE_3__ {struct device_node* node; } ;
struct op_inode_info {TYPE_1__ u; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;
struct device_node {struct property* properties; struct device_node* sibling; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  full_name; struct device_node* child; TYPE_2__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  unique_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int /*<<< orphan*/  OPENPROM_ROOT_INO ; 
 struct op_inode_info* OP_I (struct inode*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 char* kbasename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_mutex ; 
 int strlen (char*) ; 

__attribute__((used)) static int openpromfs_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct op_inode_info *oi = OP_I(inode);
	struct device_node *dp = oi->u.node;
	struct device_node *child;
	struct property *prop;
	int i;

	mutex_lock(&op_mutex);
	
	if (ctx->pos == 0) {
		if (!dir_emit(ctx, ".", 1, inode->i_ino, DT_DIR))
			goto out;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (!dir_emit(ctx, "..", 2,
			    (dp->parent == NULL ?
			     OPENPROM_ROOT_INO :
			     dp->parent->unique_id), DT_DIR))
			goto out;
		ctx->pos = 2;
	}
	i = ctx->pos - 2;

	/* First, the children nodes as directories.  */
	child = dp->child;
	while (i && child) {
		child = child->sibling;
		i--;
	}
	while (child) {
		if (!dir_emit(ctx,
			    kbasename(child->full_name),
			    strlen(kbasename(child->full_name)),
			    child->unique_id, DT_DIR))
			goto out;

		ctx->pos++;
		child = child->sibling;
	}

	/* Next, the properties as files.  */
	prop = dp->properties;
	while (i && prop) {
		prop = prop->next;
		i--;
	}
	while (prop) {
		if (!dir_emit(ctx, prop->name, strlen(prop->name),
			    prop->unique_id, DT_REG))
			goto out;

		ctx->pos++;
		prop = prop->next;
	}

out:
	mutex_unlock(&op_mutex);
	return 0;
}