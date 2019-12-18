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
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  vh_mutex; int /*<<< orphan*/  file_count; int /*<<< orphan*/  next_cnid; int /*<<< orphan*/  hidden_dir; } ;
struct dentry {int /*<<< orphan*/  d_name; void* d_fsdata; struct dentry* d_parent; } ;
typedef  int /*<<< orphan*/  cnid ;
struct TYPE_2__ {scalar_t__ linkid; } ;

/* Variables and functions */
 int EEXIST ; 
 int EPERM ; 
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 int hfsplus_create_cat (scalar_t__,struct inode*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  hfsplus_instantiate (struct dentry*,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  hfsplus_mark_mdb_dirty (int /*<<< orphan*/ ) ; 
 int hfsplus_rename_cat (scalar_t__,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct qstr*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static int hfsplus_link(struct dentry *src_dentry, struct inode *dst_dir,
			struct dentry *dst_dentry)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dst_dir->i_sb);
	struct inode *inode = d_inode(src_dentry);
	struct inode *src_dir = d_inode(src_dentry->d_parent);
	struct qstr str;
	char name[32];
	u32 cnid, id;
	int res;

	if (HFSPLUS_IS_RSRC(inode))
		return -EPERM;
	if (!S_ISREG(inode->i_mode))
		return -EPERM;

	mutex_lock(&sbi->vh_mutex);
	if (inode->i_ino == (u32)(unsigned long)src_dentry->d_fsdata) {
		for (;;) {
			get_random_bytes(&id, sizeof(cnid));
			id &= 0x3fffffff;
			str.name = name;
			str.len = sprintf(name, "iNode%d", id);
			res = hfsplus_rename_cat(inode->i_ino,
						 src_dir, &src_dentry->d_name,
						 sbi->hidden_dir, &str);
			if (!res)
				break;
			if (res != -EEXIST)
				goto out;
		}
		HFSPLUS_I(inode)->linkid = id;
		cnid = sbi->next_cnid++;
		src_dentry->d_fsdata = (void *)(unsigned long)cnid;
		res = hfsplus_create_cat(cnid, src_dir,
			&src_dentry->d_name, inode);
		if (res)
			/* panic? */
			goto out;
		sbi->file_count++;
	}
	cnid = sbi->next_cnid++;
	res = hfsplus_create_cat(cnid, dst_dir, &dst_dentry->d_name, inode);
	if (res)
		goto out;

	inc_nlink(inode);
	hfsplus_instantiate(dst_dentry, inode, cnid);
	ihold(inode);
	inode->i_ctime = current_time(inode);
	mark_inode_dirty(inode);
	sbi->file_count++;
	hfsplus_mark_mdb_dirty(dst_dir->i_sb);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}