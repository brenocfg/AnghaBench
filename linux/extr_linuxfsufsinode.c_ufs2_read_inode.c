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
typedef  int /*<<< orphan*/  umode_t ;
struct TYPE_10__ {scalar_t__* i_symlink; scalar_t__* u2_i_data; } ;
struct ufs_inode_info {TYPE_5__ i_u1; void* i_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ui_symlink; int /*<<< orphan*/  ui_addr; } ;
struct ufs2_inode {TYPE_4__ ui_u2; int /*<<< orphan*/  ui_flags; int /*<<< orphan*/  ui_gen; int /*<<< orphan*/  ui_blocks; int /*<<< orphan*/  ui_mtimensec; int /*<<< orphan*/  ui_ctimensec; int /*<<< orphan*/  ui_atimensec; int /*<<< orphan*/  ui_mtime; int /*<<< orphan*/  ui_ctime; int /*<<< orphan*/  ui_atime; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  ui_gid; int /*<<< orphan*/  ui_uid; int /*<<< orphan*/  ui_nlink; int /*<<< orphan*/  ui_mode; } ;
struct super_block {int dummy; } ;
struct TYPE_8__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_7__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {void* tv_nsec; void* tv_sec; } ;
struct inode {scalar_t__ i_nlink; void* i_blocks; void* i_generation; TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; void* i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ) ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 int /*<<< orphan*/  fs16_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufs2_read_inode(struct inode *inode, struct ufs2_inode *ufs2_inode)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	umode_t mode;

	UFSD("Reading ufs2 inode, ino %lu\n", inode->i_ino);
	/*
	 * Copy data to the in-core inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs2_inode->ui_mode);
	set_nlink(inode, fs16_to_cpu(sb, ufs2_inode->ui_nlink));
	if (inode->i_nlink == 0)
		return -ESTALE;

        /*
         * Linux now has 32-bit uid and gid, so we can support EFT.
         */
	i_uid_write(inode, fs32_to_cpu(sb, ufs2_inode->ui_uid));
	i_gid_write(inode, fs32_to_cpu(sb, ufs2_inode->ui_gid));

	inode->i_size = fs64_to_cpu(sb, ufs2_inode->ui_size);
	inode->i_atime.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_atime);
	inode->i_ctime.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_ctime);
	inode->i_mtime.tv_sec = fs64_to_cpu(sb, ufs2_inode->ui_mtime);
	inode->i_atime.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_atimensec);
	inode->i_ctime.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_ctimensec);
	inode->i_mtime.tv_nsec = fs32_to_cpu(sb, ufs2_inode->ui_mtimensec);
	inode->i_blocks = fs64_to_cpu(sb, ufs2_inode->ui_blocks);
	inode->i_generation = fs32_to_cpu(sb, ufs2_inode->ui_gen);
	ufsi->i_flags = fs32_to_cpu(sb, ufs2_inode->ui_flags);
	/*
	ufsi->i_shadow = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shadow);
	ufsi->i_oeftflag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftflag);
	*/

	if (S_ISCHR(mode) || S_ISBLK(mode) || inode->i_blocks) {
		memcpy(ufsi->i_u1.u2_i_data, &ufs2_inode->ui_u2.ui_addr,
		       sizeof(ufs2_inode->ui_u2.ui_addr));
	} else {
		memcpy(ufsi->i_u1.i_symlink, ufs2_inode->ui_u2.ui_symlink,
		       sizeof(ufs2_inode->ui_u2.ui_symlink) - 1);
		ufsi->i_u1.i_symlink[sizeof(ufs2_inode->ui_u2.ui_symlink) - 1] = 0;
	}
	return 0;
}