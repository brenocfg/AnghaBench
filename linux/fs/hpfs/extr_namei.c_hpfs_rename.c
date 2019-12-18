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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct hpfs_dirent {int hidden; int /*<<< orphan*/ * name; } ;
struct fnode {unsigned int len; int /*<<< orphan*/ * name; int /*<<< orphan*/  up; } ;
struct TYPE_3__ {unsigned char* name; unsigned int len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_4__ {int /*<<< orphan*/  i_parent_dir; int /*<<< orphan*/  i_dno; } ;

/* Variables and functions */
 int EFSERROR ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 unsigned int RENAME_NOREPLACE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  copy_de (struct hpfs_dirent*,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int hpfs_add_dirent (struct inode*,unsigned char const*,unsigned int,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_adjust_length (unsigned char const*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int hpfs_chk_name (unsigned char const*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 struct fnode* hpfs_map_fnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int hpfs_remove_dirent (struct inode*,int /*<<< orphan*/ ,struct hpfs_dirent*,struct quad_buffer_head*,int) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_update_directory_times (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 struct hpfs_dirent* map_dirent (struct inode*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hpfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		       struct inode *new_dir, struct dentry *new_dentry,
		       unsigned int flags)
{
	const unsigned char *old_name = old_dentry->d_name.name;
	unsigned old_len = old_dentry->d_name.len;
	const unsigned char *new_name = new_dentry->d_name.name;
	unsigned new_len = new_dentry->d_name.len;
	struct inode *i = d_inode(old_dentry);
	struct inode *new_inode = d_inode(new_dentry);
	struct quad_buffer_head qbh, qbh1;
	struct hpfs_dirent *dep, *nde;
	struct hpfs_dirent de;
	dnode_secno dno;
	int r;
	struct buffer_head *bh;
	struct fnode *fnode;
	int err;

	if (flags & ~RENAME_NOREPLACE)
		return -EINVAL;

	if ((err = hpfs_chk_name(new_name, &new_len))) return err;
	err = 0;
	hpfs_adjust_length(old_name, &old_len);

	hpfs_lock(i->i_sb);
	/* order doesn't matter, due to VFS exclusion */
	
	/* Erm? Moving over the empty non-busy directory is perfectly legal */
	if (new_inode && S_ISDIR(new_inode->i_mode)) {
		err = -EINVAL;
		goto end1;
	}

	if (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, old_name, old_len, &dno, &qbh))) {
		hpfs_error(i->i_sb, "lookup succeeded but map dirent failed");
		err = -ENOENT;
		goto end1;
	}
	copy_de(&de, dep);
	de.hidden = new_name[0] == '.';

	if (new_inode) {
		int r;
		if ((r = hpfs_remove_dirent(old_dir, dno, dep, &qbh, 1)) != 2) {
			if ((nde = map_dirent(new_dir, hpfs_i(new_dir)->i_dno, new_name, new_len, NULL, &qbh1))) {
				clear_nlink(new_inode);
				copy_de(nde, &de);
				memcpy(nde->name, new_name, new_len);
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brelse4(&qbh1);
				goto end;
			}
			hpfs_error(new_dir->i_sb, "hpfs_rename: could not find dirent");
			err = -EFSERROR;
			goto end1;
		}
		err = -ENOSPC;
		goto end1;
	}

	if (new_dir == old_dir) hpfs_brelse4(&qbh);

	if ((r = hpfs_add_dirent(new_dir, new_name, new_len, &de))) {
		if (r == -1) hpfs_error(new_dir->i_sb, "hpfs_rename: dirent already exists!");
		err = r == 1 ? -ENOSPC : -EFSERROR;
		if (new_dir != old_dir) hpfs_brelse4(&qbh);
		goto end1;
	}
	
	if (new_dir == old_dir)
		if (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, old_name, old_len, &dno, &qbh))) {
			hpfs_error(i->i_sb, "lookup succeeded but map dirent failed at #2");
			err = -ENOENT;
			goto end1;
		}

	if ((r = hpfs_remove_dirent(old_dir, dno, dep, &qbh, 0))) {
		hpfs_error(i->i_sb, "hpfs_rename: could not remove dirent");
		err = r == 2 ? -ENOSPC : -EFSERROR;
		goto end1;
	}

end:
	hpfs_i(i)->i_parent_dir = new_dir->i_ino;
	if (S_ISDIR(i->i_mode)) {
		inc_nlink(new_dir);
		drop_nlink(old_dir);
	}
	if ((fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) {
		fnode->up = cpu_to_le32(new_dir->i_ino);
		fnode->len = new_len;
		memcpy(fnode->name, new_name, new_len>15?15:new_len);
		if (new_len < 15) memset(&fnode->name[new_len], 0, 15 - new_len);
		mark_buffer_dirty(bh);
		brelse(bh);
	}
end1:
	if (!err) {
		hpfs_update_directory_times(old_dir);
		hpfs_update_directory_times(new_dir);
	}
	hpfs_unlock(i->i_sb);
	return err;
}