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
struct page {int dummy; } ;
struct TYPE_3__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct inode {scalar_t__ i_nlink; scalar_t__ i_generation; TYPE_1__ i_mtime; TYPE_1__ i_ctime; TYPE_1__ i_atime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_blocks; } ;
struct f2fs_inode {void* i_crtime_nsec; void* i_crtime; void* i_projid; void* i_inline_xattr_size; void* i_extra_isize; int /*<<< orphan*/  i_dir_level; void* i_generation; void* i_pino; void* i_flags; void* i_xattr_nid; void* i_gc_failures; void* i_current_depth; void* i_mtime_nsec; void* i_ctime_nsec; void* i_atime_nsec; void* i_mtime; void* i_ctime; void* i_atime; int /*<<< orphan*/  i_ext; void* i_blocks; void* i_size; void* i_links; void* i_gid; void* i_uid; int /*<<< orphan*/  i_advise; void* i_mode; } ;
struct extent_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  largest; } ;
typedef  scalar_t__ projid_t ;
struct TYPE_4__ {scalar_t__ i_current_depth; scalar_t__ i_xattr_nid; scalar_t__ i_flags; scalar_t__ i_pino; TYPE_1__ i_crtime; TYPE_1__* i_disk_time; int /*<<< orphan*/  i_extra_isize; int /*<<< orphan*/  i_projid; int /*<<< orphan*/  i_inline_xattr_size; int /*<<< orphan*/  i_dir_level; int /*<<< orphan*/ * i_gc_failures; int /*<<< orphan*/  i_advise; struct extent_tree* extent_tree; } ;

/* Variables and functions */
 scalar_t__ F2FS_FITS_IN_INODE (struct f2fs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 size_t GC_FAILURE_PIN ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ SECTOR_TO_BLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_inode_rdev (struct inode*,struct f2fs_inode*) ; 
 int /*<<< orphan*/  clear_inline_node (struct page*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ f2fs_has_extra_attr (struct inode*) ; 
 int /*<<< orphan*/  f2fs_inode_chksum_set (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  f2fs_inode_synced (struct inode*) ; 
 scalar_t__ f2fs_sb_has_flexible_inline_xattr (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_sb_has_inode_crtime (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_sb_has_project_quota (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ from_kprojid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_crtime ; 
 scalar_t__ i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_projid ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_raw_extent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_raw_inline (struct inode*,struct f2fs_inode*) ; 

void f2fs_update_inode(struct inode *inode, struct page *node_page)
{
	struct f2fs_inode *ri;
	struct extent_tree *et = F2FS_I(inode)->extent_tree;

	f2fs_wait_on_page_writeback(node_page, NODE, true, true);
	set_page_dirty(node_page);

	f2fs_inode_synced(inode);

	ri = F2FS_INODE(node_page);

	ri->i_mode = cpu_to_le16(inode->i_mode);
	ri->i_advise = F2FS_I(inode)->i_advise;
	ri->i_uid = cpu_to_le32(i_uid_read(inode));
	ri->i_gid = cpu_to_le32(i_gid_read(inode));
	ri->i_links = cpu_to_le32(inode->i_nlink);
	ri->i_size = cpu_to_le64(i_size_read(inode));
	ri->i_blocks = cpu_to_le64(SECTOR_TO_BLOCK(inode->i_blocks) + 1);

	if (et) {
		read_lock(&et->lock);
		set_raw_extent(&et->largest, &ri->i_ext);
		read_unlock(&et->lock);
	} else {
		memset(&ri->i_ext, 0, sizeof(ri->i_ext));
	}
	set_raw_inline(inode, ri);

	ri->i_atime = cpu_to_le64(inode->i_atime.tv_sec);
	ri->i_ctime = cpu_to_le64(inode->i_ctime.tv_sec);
	ri->i_mtime = cpu_to_le64(inode->i_mtime.tv_sec);
	ri->i_atime_nsec = cpu_to_le32(inode->i_atime.tv_nsec);
	ri->i_ctime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	ri->i_mtime_nsec = cpu_to_le32(inode->i_mtime.tv_nsec);
	if (S_ISDIR(inode->i_mode))
		ri->i_current_depth =
			cpu_to_le32(F2FS_I(inode)->i_current_depth);
	else if (S_ISREG(inode->i_mode))
		ri->i_gc_failures =
			cpu_to_le16(F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN]);
	ri->i_xattr_nid = cpu_to_le32(F2FS_I(inode)->i_xattr_nid);
	ri->i_flags = cpu_to_le32(F2FS_I(inode)->i_flags);
	ri->i_pino = cpu_to_le32(F2FS_I(inode)->i_pino);
	ri->i_generation = cpu_to_le32(inode->i_generation);
	ri->i_dir_level = F2FS_I(inode)->i_dir_level;

	if (f2fs_has_extra_attr(inode)) {
		ri->i_extra_isize = cpu_to_le16(F2FS_I(inode)->i_extra_isize);

		if (f2fs_sb_has_flexible_inline_xattr(F2FS_I_SB(inode)))
			ri->i_inline_xattr_size =
				cpu_to_le16(F2FS_I(inode)->i_inline_xattr_size);

		if (f2fs_sb_has_project_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, F2FS_I(inode)->i_extra_isize,
								i_projid)) {
			projid_t i_projid;

			i_projid = from_kprojid(&init_user_ns,
						F2FS_I(inode)->i_projid);
			ri->i_projid = cpu_to_le32(i_projid);
		}

		if (f2fs_sb_has_inode_crtime(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, F2FS_I(inode)->i_extra_isize,
								i_crtime)) {
			ri->i_crtime =
				cpu_to_le64(F2FS_I(inode)->i_crtime.tv_sec);
			ri->i_crtime_nsec =
				cpu_to_le32(F2FS_I(inode)->i_crtime.tv_nsec);
		}
	}

	__set_inode_rdev(inode, ri);

	/* deleted inode */
	if (inode->i_nlink == 0)
		clear_inline_node(node_page);

	F2FS_I(inode)->i_disk_time[0] = inode->i_atime;
	F2FS_I(inode)->i_disk_time[1] = inode->i_ctime;
	F2FS_I(inode)->i_disk_time[2] = inode->i_mtime;
	F2FS_I(inode)->i_disk_time[3] = F2FS_I(inode)->i_crtime;

#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_I_SB(inode), node_page);
#endif
}