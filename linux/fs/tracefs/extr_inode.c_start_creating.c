#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {scalar_t__ d_inode; } ;
struct TYPE_4__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 int EEXIST ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (scalar_t__) ; 
 int /*<<< orphan*/  inode_unlock (scalar_t__) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int simple_pin_fs (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  trace_fs_type ; 
 TYPE_1__* tracefs_mount ; 
 int /*<<< orphan*/  tracefs_mount_count ; 

__attribute__((used)) static struct dentry *start_creating(const char *name, struct dentry *parent)
{
	struct dentry *dentry;
	int error;

	pr_debug("tracefs: creating file '%s'\n",name);

	error = simple_pin_fs(&trace_fs_type, &tracefs_mount,
			      &tracefs_mount_count);
	if (error)
		return ERR_PTR(error);

	/* If the parent is not specified, we create it in the root.
	 * We need the root dentry to do this, which is in the super
	 * block. A pointer to that is in the struct vfsmount that we
	 * have around.
	 */
	if (!parent)
		parent = tracefs_mount->mnt_root;

	inode_lock(parent->d_inode);
	dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(dentry) && dentry->d_inode) {
		dput(dentry);
		dentry = ERR_PTR(-EEXIST);
	}

	if (IS_ERR(dentry)) {
		inode_unlock(parent->d_inode);
		simple_release_fs(&tracefs_mount, &tracefs_mount_count);
	}

	return dentry;
}