#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct TYPE_11__ {scalar_t__* i_symlink; scalar_t__* i_data; } ;
struct ufs_inode_info {TYPE_10__ i_u1; void* i_oeftflag; void* i_shadow; void* i_flags; } ;
struct TYPE_20__ {int /*<<< orphan*/ * ui_symlink; int /*<<< orphan*/  ui_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  ui_oeftflag; int /*<<< orphan*/  ui_shadow; } ;
struct TYPE_19__ {TYPE_7__ ui_sun; } ;
struct TYPE_14__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_sec; } ;
struct ufs_inode {TYPE_9__ ui_u2; TYPE_8__ ui_u3; int /*<<< orphan*/  ui_flags; int /*<<< orphan*/  ui_gen; int /*<<< orphan*/  ui_blocks; TYPE_3__ ui_mtime; TYPE_2__ ui_ctime; TYPE_1__ ui_atime; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  ui_nlink; int /*<<< orphan*/  ui_mode; } ;
struct super_block {int dummy; } ;
struct TYPE_17__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_16__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_15__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct inode {scalar_t__ i_nlink; void* i_blocks; void* i_generation; TYPE_6__ i_ctime; TYPE_5__ i_atime; TYPE_4__ i_mtime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 int /*<<< orphan*/  fs16_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_get_inode_gid (struct super_block*,struct ufs_inode*) ; 
 int /*<<< orphan*/  ufs_get_inode_uid (struct super_block*,struct ufs_inode*) ; 

__attribute__((used)) static int ufs1_read_inode(struct inode *inode, struct ufs_inode *ufs_inode)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	umode_t mode;

	/*
	 * Copy data to the in-core inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs_inode->ui_mode);
	set_nlink(inode, fs16_to_cpu(sb, ufs_inode->ui_nlink));
	if (inode->i_nlink == 0)
		return -ESTALE;

	/*
	 * Linux now has 32-bit uid and gid, so we can support EFT.
	 */
	i_uid_write(inode, ufs_get_inode_uid(sb, ufs_inode));
	i_gid_write(inode, ufs_get_inode_gid(sb, ufs_inode));

	inode->i_size = fs64_to_cpu(sb, ufs_inode->ui_size);
	inode->i_atime.tv_sec = (signed)fs32_to_cpu(sb, ufs_inode->ui_atime.tv_sec);
	inode->i_ctime.tv_sec = (signed)fs32_to_cpu(sb, ufs_inode->ui_ctime.tv_sec);
	inode->i_mtime.tv_sec = (signed)fs32_to_cpu(sb, ufs_inode->ui_mtime.tv_sec);
	inode->i_mtime.tv_nsec = 0;
	inode->i_atime.tv_nsec = 0;
	inode->i_ctime.tv_nsec = 0;
	inode->i_blocks = fs32_to_cpu(sb, ufs_inode->ui_blocks);
	inode->i_generation = fs32_to_cpu(sb, ufs_inode->ui_gen);
	ufsi->i_flags = fs32_to_cpu(sb, ufs_inode->ui_flags);
	ufsi->i_shadow = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shadow);
	ufsi->i_oeftflag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftflag);


	if (S_ISCHR(mode) || S_ISBLK(mode) || inode->i_blocks) {
		memcpy(ufsi->i_u1.i_data, &ufs_inode->ui_u2.ui_addr,
		       sizeof(ufs_inode->ui_u2.ui_addr));
	} else {
		memcpy(ufsi->i_u1.i_symlink, ufs_inode->ui_u2.ui_symlink,
		       sizeof(ufs_inode->ui_u2.ui_symlink) - 1);
		ufsi->i_u1.i_symlink[sizeof(ufs_inode->ui_u2.ui_symlink) - 1] = 0;
	}
	return 0;
}