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
struct quad_buffer_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hpfs_dirent {int /*<<< orphan*/  directory; scalar_t__ first; } ;
struct TYPE_3__ {unsigned char* name; unsigned int len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_4__ {int /*<<< orphan*/  i_dno; } ;

/* Variables and functions */
 int EFSERROR ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  hpfs_adjust_length (unsigned char const*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_count_dnodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 int hpfs_remove_dirent (struct inode*,int /*<<< orphan*/ ,struct hpfs_dirent*,struct quad_buffer_head*,int) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_update_directory_times (struct inode*) ; 
 struct hpfs_dirent* map_dirent (struct inode*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 

__attribute__((used)) static int hpfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	const unsigned char *name = dentry->d_name.name;
	unsigned len = dentry->d_name.len;
	struct quad_buffer_head qbh;
	struct hpfs_dirent *de;
	struct inode *inode = d_inode(dentry);
	dnode_secno dno;
	int n_items = 0;
	int err;
	int r;

	hpfs_adjust_length(name, &len);
	hpfs_lock(dir->i_sb);
	err = -ENOENT;
	de = map_dirent(dir, hpfs_i(dir)->i_dno, name, len, &dno, &qbh);
	if (!de)
		goto out;

	err = -EPERM;
	if (de->first)
		goto out1;

	err = -ENOTDIR;
	if (!de->directory)
		goto out1;

	hpfs_count_dnodes(dir->i_sb, hpfs_i(inode)->i_dno, NULL, NULL, &n_items);
	err = -ENOTEMPTY;
	if (n_items)
		goto out1;

	r = hpfs_remove_dirent(dir, dno, de, &qbh, 1);
	switch (r) {
	case 1:
		hpfs_error(dir->i_sb, "there was error when removing dirent");
		err = -EFSERROR;
		break;
	case 2:
		err = -ENOSPC;
		break;
	default:
		drop_nlink(dir);
		clear_nlink(inode);
		err = 0;
	}
	goto out;
out1:
	hpfs_brelse4(&qbh);
out:
	if (!err)
		hpfs_update_directory_times(dir);
	hpfs_unlock(dir->i_sb);
	return err;
}