#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct dentry* d_parent; } ;
struct autofs_sb_info {int flags; int version; int /*<<< orphan*/  lookup_lock; } ;
struct autofs_info {int /*<<< orphan*/  dentry; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {scalar_t__ i_size; } ;

/* Variables and functions */
 int AUTOFS_SBI_CATATONIC ; 
 int EACCES ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  __autofs_add_expiring (struct dentry*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_clear_leaf_automount_flags (struct dentry*) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs_dir_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	struct autofs_info *p_ino;

	pr_debug("dentry %p, removing %pd\n", dentry, dentry);

	if (!autofs_oz_mode(sbi))
		return -EACCES;

	/* autofs_oz_mode() needs to allow path walks when the
	 * autofs mount is catatonic but the state of an autofs
	 * file system needs to be preserved over restarts.
	 */
	if (sbi->flags & AUTOFS_SBI_CATATONIC)
		return -EACCES;

	spin_lock(&sbi->lookup_lock);
	if (!simple_empty(dentry)) {
		spin_unlock(&sbi->lookup_lock);
		return -ENOTEMPTY;
	}
	__autofs_add_expiring(dentry);
	d_drop(dentry);
	spin_unlock(&sbi->lookup_lock);

	if (sbi->version < 5)
		autofs_clear_leaf_automount_flags(dentry);

	if (atomic_dec_and_test(&ino->count)) {
		p_ino = autofs_dentry_ino(dentry->d_parent);
		if (p_ino && dentry->d_parent != dentry)
			atomic_dec(&p_ino->count);
	}
	dput(ino->dentry);
	d_inode(dentry)->i_size = 0;
	clear_nlink(d_inode(dentry));

	if (dir->i_nlink)
		drop_nlink(dir);

	return 0;
}