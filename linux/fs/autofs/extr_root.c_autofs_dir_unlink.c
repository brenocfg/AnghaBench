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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct dentry* d_parent; } ;
struct autofs_sb_info {int flags; int /*<<< orphan*/  lookup_lock; } ;
struct autofs_info {int /*<<< orphan*/  dentry; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {scalar_t__ i_size; } ;

/* Variables and functions */
 int AUTOFS_SBI_CATATONIC ; 
 int EACCES ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  __autofs_add_expiring (struct dentry*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs_dir_unlink(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	struct autofs_info *p_ino;

	if (!autofs_oz_mode(sbi))
		return -EACCES;

	/* autofs_oz_mode() needs to allow path walks when the
	 * autofs mount is catatonic but the state of an autofs
	 * file system needs to be preserved over restarts.
	 */
	if (sbi->flags & AUTOFS_SBI_CATATONIC)
		return -EACCES;

	if (atomic_dec_and_test(&ino->count)) {
		p_ino = autofs_dentry_ino(dentry->d_parent);
		if (p_ino && !IS_ROOT(dentry))
			atomic_dec(&p_ino->count);
	}
	dput(ino->dentry);

	d_inode(dentry)->i_size = 0;
	clear_nlink(d_inode(dentry));

	dir->i_mtime = current_time(dir);

	spin_lock(&sbi->lookup_lock);
	__autofs_add_expiring(dentry);
	d_drop(dentry);
	spin_unlock(&sbi->lookup_lock);

	return 0;
}