#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct jfs_sb_info {int inostamp; int umask; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct jfs_inode_info {int fileset; int mode2; int next_index; int otime; int acltype; int dev; int /*<<< orphan*/  ea; int /*<<< orphan*/  acl; int /*<<< orphan*/  ixpxd; int /*<<< orphan*/  saved_gid; int /*<<< orphan*/  saved_uid; } ;
struct TYPE_13__ {int tv_sec; int tv_nsec; } ;
struct TYPE_11__ {int tv_sec; int tv_nsec; } ;
struct TYPE_9__ {int tv_sec; int tv_nsec; } ;
struct inode {int i_ino; int i_generation; int i_nlink; int i_mode; TYPE_6__ i_mtime; TYPE_4__ i_ctime; TYPE_2__ i_atime; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_size; } ;
struct TYPE_14__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_12__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_10__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_8__ {void* tv_nsec; void* tv_sec; } ;
struct dinode {void* di_rdev; void* di_acltype; TYPE_7__ di_otime; void* di_next_index; int /*<<< orphan*/  di_ea; int /*<<< orphan*/  di_acl; int /*<<< orphan*/  di_ixpxd; TYPE_5__ di_mtime; TYPE_3__ di_ctime; TYPE_1__ di_atime; void* di_mode; void* di_gid; void* di_uid; void* di_nlink; void* di_nblocks; void* di_size; void* di_gen; void* di_number; void* di_inostamp; void* di_fileset; } ;

/* Variables and functions */
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBLK2LBLK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int i_gid_read (struct inode*) ; 
 int i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_to_dinode(struct dinode * dip, struct inode *ip)
{
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);

	dip->di_fileset = cpu_to_le32(jfs_ip->fileset);
	dip->di_inostamp = cpu_to_le32(sbi->inostamp);
	dip->di_number = cpu_to_le32(ip->i_ino);
	dip->di_gen = cpu_to_le32(ip->i_generation);
	dip->di_size = cpu_to_le64(ip->i_size);
	dip->di_nblocks = cpu_to_le64(PBLK2LBLK(ip->i_sb, ip->i_blocks));
	dip->di_nlink = cpu_to_le32(ip->i_nlink);
	if (!uid_valid(sbi->uid))
		dip->di_uid = cpu_to_le32(i_uid_read(ip));
	else
		dip->di_uid =cpu_to_le32(from_kuid(&init_user_ns,
						   jfs_ip->saved_uid));
	if (!gid_valid(sbi->gid))
		dip->di_gid = cpu_to_le32(i_gid_read(ip));
	else
		dip->di_gid = cpu_to_le32(from_kgid(&init_user_ns,
						    jfs_ip->saved_gid));
	/*
	 * mode2 is only needed for storing the higher order bits.
	 * Trust i_mode for the lower order ones
	 */
	if (sbi->umask == -1)
		dip->di_mode = cpu_to_le32((jfs_ip->mode2 & 0xffff0000) |
					   ip->i_mode);
	else /* Leave the original permissions alone */
		dip->di_mode = cpu_to_le32(jfs_ip->mode2);

	dip->di_atime.tv_sec = cpu_to_le32(ip->i_atime.tv_sec);
	dip->di_atime.tv_nsec = cpu_to_le32(ip->i_atime.tv_nsec);
	dip->di_ctime.tv_sec = cpu_to_le32(ip->i_ctime.tv_sec);
	dip->di_ctime.tv_nsec = cpu_to_le32(ip->i_ctime.tv_nsec);
	dip->di_mtime.tv_sec = cpu_to_le32(ip->i_mtime.tv_sec);
	dip->di_mtime.tv_nsec = cpu_to_le32(ip->i_mtime.tv_nsec);
	dip->di_ixpxd = jfs_ip->ixpxd;	/* in-memory pxd's are little-endian */
	dip->di_acl = jfs_ip->acl;	/* as are dxd's */
	dip->di_ea = jfs_ip->ea;
	dip->di_next_index = cpu_to_le32(jfs_ip->next_index);
	dip->di_otime.tv_sec = cpu_to_le32(jfs_ip->otime);
	dip->di_otime.tv_nsec = 0;
	dip->di_acltype = cpu_to_le32(jfs_ip->acltype);
	if (S_ISCHR(ip->i_mode) || S_ISBLK(ip->i_mode))
		dip->di_rdev = cpu_to_le32(jfs_ip->dev);
}