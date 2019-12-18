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
typedef  scalar_t__ u32 ;
struct qstr {char* name; int /*<<< orphan*/  len; } ;
struct inode {scalar_t__ i_ino; scalar_t__ i_nlink; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_sb; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  vh_mutex; int /*<<< orphan*/  file_count; struct inode* hidden_dir; } ;
struct dentry {int /*<<< orphan*/  d_name; scalar_t__ d_fsdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  opencnt; } ;

/* Variables and functions */
 int EPERM ; 
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_DEAD ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int hfsplus_delete_cat (scalar_t__,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int hfsplus_rename_cat (scalar_t__,struct inode*,int /*<<< orphan*/ *,struct inode*,struct qstr*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static int hfsplus_unlink(struct inode *dir, struct dentry *dentry)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	struct inode *inode = d_inode(dentry);
	struct qstr str;
	char name[32];
	u32 cnid;
	int res;

	if (HFSPLUS_IS_RSRC(inode))
		return -EPERM;

	mutex_lock(&sbi->vh_mutex);
	cnid = (u32)(unsigned long)dentry->d_fsdata;
	if (inode->i_ino == cnid &&
	    atomic_read(&HFSPLUS_I(inode)->opencnt)) {
		str.name = name;
		str.len = sprintf(name, "temp%lu", inode->i_ino);
		res = hfsplus_rename_cat(inode->i_ino,
					 dir, &dentry->d_name,
					 sbi->hidden_dir, &str);
		if (!res) {
			inode->i_flags |= S_DEAD;
			drop_nlink(inode);
		}
		goto out;
	}
	res = hfsplus_delete_cat(cnid, dir, &dentry->d_name);
	if (res)
		goto out;

	if (inode->i_nlink > 0)
		drop_nlink(inode);
	if (inode->i_ino == cnid)
		clear_nlink(inode);
	if (!inode->i_nlink) {
		if (inode->i_ino != cnid) {
			sbi->file_count--;
			if (!atomic_read(&HFSPLUS_I(inode)->opencnt)) {
				res = hfsplus_delete_cat(inode->i_ino,
							 sbi->hidden_dir,
							 NULL);
				if (!res)
					hfsplus_delete_inode(inode);
			} else
				inode->i_flags |= S_DEAD;
		} else
			hfsplus_delete_inode(inode);
	} else
		sbi->file_count--;
	inode->i_ctime = current_time(inode);
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}