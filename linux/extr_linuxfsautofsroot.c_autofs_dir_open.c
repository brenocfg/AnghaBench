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
struct inode {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  lookup_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int dcache_dir_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  path_is_mountpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct file*,struct dentry*,struct dentry*) ; 
 scalar_t__ simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs_dir_open(struct inode *inode, struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);

	pr_debug("file=%p dentry=%p %pd\n", file, dentry, dentry);

	if (autofs_oz_mode(sbi))
		goto out;

	/*
	 * An empty directory in an autofs file system is always a
	 * mount point. The daemon must have failed to mount this
	 * during lookup so it doesn't exist. This can happen, for
	 * example, if user space returns an incorrect status for a
	 * mount request. Otherwise we're doing a readdir on the
	 * autofs file system so just let the libfs routines handle
	 * it.
	 */
	spin_lock(&sbi->lookup_lock);
	if (!path_is_mountpoint(&file->f_path) && simple_empty(dentry)) {
		spin_unlock(&sbi->lookup_lock);
		return -ENOENT;
	}
	spin_unlock(&sbi->lookup_lock);

out:
	return dcache_dir_open(inode, file);
}