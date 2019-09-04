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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; struct kernfs_super_info* s_fs_info; } ;
struct kernfs_super_info {int /*<<< orphan*/  node; void const* ns; struct kernfs_root* root; } ;
struct kernfs_root {int /*<<< orphan*/  supers; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* ERR_CAST (struct super_block*) ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int kernfs_fill_super (struct super_block*,unsigned long) ; 
 struct kernfs_super_info* kernfs_info (struct super_block*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  kernfs_set_super ; 
 int /*<<< orphan*/  kernfs_test_super ; 
 int /*<<< orphan*/  kfree (struct kernfs_super_info*) ; 
 struct kernfs_super_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct super_block* sget_userns (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct kernfs_super_info*) ; 

struct dentry *kernfs_mount_ns(struct file_system_type *fs_type, int flags,
				struct kernfs_root *root, unsigned long magic,
				bool *new_sb_created, const void *ns)
{
	struct super_block *sb;
	struct kernfs_super_info *info;
	int error;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return ERR_PTR(-ENOMEM);

	info->root = root;
	info->ns = ns;
	INIT_LIST_HEAD(&info->node);

	sb = sget_userns(fs_type, kernfs_test_super, kernfs_set_super, flags,
			 &init_user_ns, info);
	if (IS_ERR(sb) || sb->s_fs_info != info)
		kfree(info);
	if (IS_ERR(sb))
		return ERR_CAST(sb);

	if (new_sb_created)
		*new_sb_created = !sb->s_root;

	if (!sb->s_root) {
		struct kernfs_super_info *info = kernfs_info(sb);

		error = kernfs_fill_super(sb, magic);
		if (error) {
			deactivate_locked_super(sb);
			return ERR_PTR(error);
		}
		sb->s_flags |= SB_ACTIVE;

		mutex_lock(&kernfs_mutex);
		list_add(&info->node, &root->supers);
		mutex_unlock(&kernfs_mutex);
	}

	return dget(sb->s_root);
}