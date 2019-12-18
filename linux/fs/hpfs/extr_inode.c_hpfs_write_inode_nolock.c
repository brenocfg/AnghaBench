#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct quad_buffer_head {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {scalar_t__ i_ino; int i_mode; int /*<<< orphan*/  i_sb; TYPE_3__ i_ctime; TYPE_2__ i_atime; TYPE_1__ i_mtime; int /*<<< orphan*/  i_size; scalar_t__ i_nlink; } ;
struct hpfs_inode_info {int /*<<< orphan*/  i_dno; int /*<<< orphan*/  i_ea_size; } ;
struct hpfs_dirent {int read_only; void* file_size; void* ea_size; void* creation_date; void* read_date; void* write_date; } ;
struct fnode {void* file_size; } ;
struct buffer_head {int dummy; } ;
struct TYPE_8__ {scalar_t__ sb_root; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmt_to_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*,unsigned long) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 struct fnode* hpfs_map_fnode (int /*<<< orphan*/ ,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 TYPE_4__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_write_inode_ea (struct inode*,struct fnode*) ; 
 struct hpfs_dirent* map_dirent (struct inode*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 
 struct hpfs_dirent* map_fnode_dirent (int /*<<< orphan*/ ,scalar_t__,struct fnode*,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 

void hpfs_write_inode_nolock(struct inode *i)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	struct buffer_head *bh;
	struct fnode *fnode;
	struct quad_buffer_head qbh;
	struct hpfs_dirent *de;
	if (i->i_ino == hpfs_sb(i->i_sb)->sb_root) return;
	if (!(fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) return;
	if (i->i_ino != hpfs_sb(i->i_sb)->sb_root && i->i_nlink) {
		if (!(de = map_fnode_dirent(i->i_sb, i->i_ino, fnode, &qbh))) {
			brelse(bh);
			return;
		}
	} else de = NULL;
	if (S_ISREG(i->i_mode)) {
		fnode->file_size = cpu_to_le32(i->i_size);
		if (de) de->file_size = cpu_to_le32(i->i_size);
	} else if (S_ISDIR(i->i_mode)) {
		fnode->file_size = cpu_to_le32(0);
		if (de) de->file_size = cpu_to_le32(0);
	}
	hpfs_write_inode_ea(i, fnode);
	if (de) {
		de->write_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_mtime.tv_sec));
		de->read_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_atime.tv_sec));
		de->creation_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_ctime.tv_sec));
		de->read_only = !(i->i_mode & 0222);
		de->ea_size = cpu_to_le32(hpfs_inode->i_ea_size);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
	}
	if (S_ISDIR(i->i_mode)) {
		if ((de = map_dirent(i, hpfs_inode->i_dno, "\001\001", 2, NULL, &qbh))) {
			de->write_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_mtime.tv_sec));
			de->read_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_atime.tv_sec));
			de->creation_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_ctime.tv_sec));
			de->read_only = !(i->i_mode & 0222);
			de->ea_size = cpu_to_le32(/*hpfs_inode->i_ea_size*/0);
			de->file_size = cpu_to_le32(0);
			hpfs_mark_4buffers_dirty(&qbh);
			hpfs_brelse4(&qbh);
		} else
			hpfs_error(i->i_sb,
				"directory %08lx doesn't have '.' entry",
				(unsigned long)i->i_ino);
	}
	mark_buffer_dirty(bh);
	brelse(bh);
}