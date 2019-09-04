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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_lock; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSDOS_NAME ; 
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 unsigned int RENAME_NOREPLACE ; 
 int do_msdos_rename (struct inode*,unsigned char*,struct dentry*,struct inode*,unsigned char*,struct dentry*,int) ; 
 int fat_flush_inodes (struct super_block*,struct inode*,struct inode*) ; 
 int msdos_format_name (char*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msdos_rename(struct inode *old_dir, struct dentry *old_dentry,
			struct inode *new_dir, struct dentry *new_dentry,
			unsigned int flags)
{
	struct super_block *sb = old_dir->i_sb;
	unsigned char old_msdos_name[MSDOS_NAME], new_msdos_name[MSDOS_NAME];
	int err, is_hid;

	if (flags & ~RENAME_NOREPLACE)
		return -EINVAL;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = msdos_format_name(old_dentry->d_name.name,
				old_dentry->d_name.len, old_msdos_name,
				&MSDOS_SB(old_dir->i_sb)->options);
	if (err)
		goto out;
	err = msdos_format_name(new_dentry->d_name.name,
				new_dentry->d_name.len, new_msdos_name,
				&MSDOS_SB(new_dir->i_sb)->options);
	if (err)
		goto out;

	is_hid =
	     (new_dentry->d_name.name[0] == '.') && (new_msdos_name[0] != '.');

	err = do_msdos_rename(old_dir, old_msdos_name, old_dentry,
			      new_dir, new_msdos_name, new_dentry, is_hid);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	if (!err)
		err = fat_flush_inodes(sb, old_dir, new_dir);
	return err;
}