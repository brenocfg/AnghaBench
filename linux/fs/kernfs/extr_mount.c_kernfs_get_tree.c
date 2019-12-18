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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; } ;
struct kernfs_super_info {TYPE_1__* root; int /*<<< orphan*/  node; int /*<<< orphan*/  ns; } ;
struct kernfs_fs_context {int new_sb_created; int /*<<< orphan*/  ns_tag; TYPE_1__* root; } ;
struct fs_context {int /*<<< orphan*/  root; struct kernfs_super_info* s_fs_info; struct kernfs_fs_context* fs_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  supers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int kernfs_fill_super (struct super_block*,struct kernfs_fs_context*) ; 
 struct kernfs_super_info* kernfs_info (struct super_block*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  kernfs_set_super ; 
 int /*<<< orphan*/  kernfs_test_super ; 
 struct kernfs_super_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct super_block* sget_fc (struct fs_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kernfs_get_tree(struct fs_context *fc)
{
	struct kernfs_fs_context *kfc = fc->fs_private;
	struct super_block *sb;
	struct kernfs_super_info *info;
	int error;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->root = kfc->root;
	info->ns = kfc->ns_tag;
	INIT_LIST_HEAD(&info->node);

	fc->s_fs_info = info;
	sb = sget_fc(fc, kernfs_test_super, kernfs_set_super);
	if (IS_ERR(sb))
		return PTR_ERR(sb);

	if (!sb->s_root) {
		struct kernfs_super_info *info = kernfs_info(sb);

		kfc->new_sb_created = true;

		error = kernfs_fill_super(sb, kfc);
		if (error) {
			deactivate_locked_super(sb);
			return error;
		}
		sb->s_flags |= SB_ACTIVE;

		mutex_lock(&kernfs_mutex);
		list_add(&info->node, &info->root->supers);
		mutex_unlock(&kernfs_mutex);
	}

	fc->root = dget(sb->s_root);
	return 0;
}