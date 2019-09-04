#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct hpfs_inode_info {int /*<<< orphan*/  i_dno; } ;
struct file {int f_pos; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESPIPE ; 
 int SEEK_DATA ; 
 int SEEK_HOLE ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ hpfs_add_pos (struct inode*,int*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 scalar_t__ hpfs_de_as_down_as_possible (struct super_block*,int /*<<< orphan*/ ) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_unlock (struct super_block*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ map_pos_dirent (struct inode*,int*,struct quad_buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static loff_t hpfs_dir_lseek(struct file *filp, loff_t off, int whence)
{
	loff_t new_off = off + (whence == 1 ? filp->f_pos : 0);
	loff_t pos;
	struct quad_buffer_head qbh;
	struct inode *i = file_inode(filp);
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	struct super_block *s = i->i_sb;

	/* Somebody else will have to figure out what to do here */
	if (whence == SEEK_DATA || whence == SEEK_HOLE)
		return -EINVAL;

	inode_lock(i);
	hpfs_lock(s);

	/*pr_info("dir lseek\n");*/
	if (new_off == 0 || new_off == 1 || new_off == 11 || new_off == 12 || new_off == 13) goto ok;
	pos = ((loff_t) hpfs_de_as_down_as_possible(s, hpfs_inode->i_dno) << 4) + 1;
	while (pos != new_off) {
		if (map_pos_dirent(i, &pos, &qbh)) hpfs_brelse4(&qbh);
		else goto fail;
		if (pos == 12) goto fail;
	}
	if (unlikely(hpfs_add_pos(i, &filp->f_pos) < 0)) {
		hpfs_unlock(s);
		inode_unlock(i);
		return -ENOMEM;
	}
ok:
	filp->f_pos = new_off;
	hpfs_unlock(s);
	inode_unlock(i);
	return new_off;
fail:
	/*pr_warn("illegal lseek: %016llx\n", new_off);*/
	hpfs_unlock(s);
	inode_unlock(i);
	return -ESPIPE;
}