#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fs_gid; int /*<<< orphan*/  fs_uid; } ;
struct msdos_sb_info {int dir_entries; int cluster_size; scalar_t__ root_cluster; int /*<<< orphan*/  dir_ops; TYPE_1__ options; } ;
struct msdos_dir_entry {int dummy; } ;
struct TYPE_9__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct inode {int i_size; int i_blocks; TYPE_4__ i_ctime; TYPE_3__ i_atime; TYPE_2__ i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_op; int /*<<< orphan*/  i_mode; scalar_t__ i_generation; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;
typedef  int loff_t ;
struct TYPE_10__ {int mmu_private; scalar_t__ i_logstart; scalar_t__ i_start; int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DIR ; 
 TYPE_5__* MSDOS_I (struct inode*) ; 
 int /*<<< orphan*/  MSDOS_ROOT_INO ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IRWXUGO ; 
 int fat_calc_dir_size (struct inode*) ; 
 int /*<<< orphan*/  fat_dir_operations ; 
 int /*<<< orphan*/  fat_make_mode (struct msdos_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_save_attrs (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ fat_subdirs (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 scalar_t__ is_fat32 (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,scalar_t__) ; 

__attribute__((used)) static int fat_read_root(struct inode *inode)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	int error;

	MSDOS_I(inode)->i_pos = MSDOS_ROOT_INO;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_iversion(inode);
	inode->i_generation = 0;
	inode->i_mode = fat_make_mode(sbi, ATTR_DIR, S_IRWXUGO);
	inode->i_op = sbi->dir_ops;
	inode->i_fop = &fat_dir_operations;
	if (is_fat32(sbi)) {
		MSDOS_I(inode)->i_start = sbi->root_cluster;
		error = fat_calc_dir_size(inode);
		if (error < 0)
			return error;
	} else {
		MSDOS_I(inode)->i_start = 0;
		inode->i_size = sbi->dir_entries * sizeof(struct msdos_dir_entry);
	}
	inode->i_blocks = ((inode->i_size + (sbi->cluster_size - 1))
			   & ~((loff_t)sbi->cluster_size - 1)) >> 9;
	MSDOS_I(inode)->i_logstart = 0;
	MSDOS_I(inode)->mmu_private = inode->i_size;

	fat_save_attrs(inode, ATTR_DIR);
	inode->i_mtime.tv_sec = inode->i_atime.tv_sec = inode->i_ctime.tv_sec = 0;
	inode->i_mtime.tv_nsec = inode->i_atime.tv_nsec = inode->i_ctime.tv_nsec = 0;
	set_nlink(inode, fat_subdirs(inode)+2);

	return 0;
}