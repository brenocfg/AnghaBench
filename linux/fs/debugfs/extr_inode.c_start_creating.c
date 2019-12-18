#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_6__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 int EEXIST ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  debug_fs_type ; 
 TYPE_2__* debugfs_mount ; 
 int /*<<< orphan*/  debugfs_mount_count ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int simple_pin_fs (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct dentry *start_creating(const char *name, struct dentry *parent)
{
	struct dentry *dentry;
	int error;

	pr_debug("creating file '%s'\n", name);

	if (IS_ERR(parent))
		return parent;

	error = simple_pin_fs(&debug_fs_type, &debugfs_mount,
			      &debugfs_mount_count);
	if (error) {
		pr_err("Unable to pin filesystem for file '%s'\n", name);
		return ERR_PTR(error);
	}

	/* If the parent is not specified, we create it in the root.
	 * We need the root dentry to do this, which is in the super
	 * block. A pointer to that is in the struct vfsmount that we
	 * have around.
	 */
	if (!parent)
		parent = debugfs_mount->mnt_root;

	inode_lock(d_inode(parent));
	dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(dentry) && d_really_is_positive(dentry)) {
		if (d_is_dir(dentry))
			pr_err("Directory '%s' with parent '%s' already present!\n",
			       name, parent->d_name.name);
		else
			pr_err("File '%s' in directory '%s' already present!\n",
			       name, parent->d_name.name);
		dput(dentry);
		dentry = ERR_PTR(-EEXIST);
	}

	if (IS_ERR(dentry)) {
		inode_unlock(d_inode(parent));
		simple_release_fs(&debugfs_mount, &debugfs_mount_count);
	}

	return dentry;
}