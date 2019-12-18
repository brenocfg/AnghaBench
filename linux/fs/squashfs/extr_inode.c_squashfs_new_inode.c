#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct super_block {int dummy; } ;
struct squashfs_base_inode {int /*<<< orphan*/  mode; int /*<<< orphan*/  mtime; int /*<<< orphan*/  inode_number; int /*<<< orphan*/  guid; int /*<<< orphan*/  uid; } ;
struct TYPE_6__ {void* tv_sec; } ;
struct TYPE_5__ {void* tv_sec; } ;
struct TYPE_4__ {void* tv_sec; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; void* i_ino; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int squashfs_get_id (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int squashfs_new_inode(struct super_block *sb, struct inode *inode,
				struct squashfs_base_inode *sqsh_ino)
{
	uid_t i_uid;
	gid_t i_gid;
	int err;

	err = squashfs_get_id(sb, le16_to_cpu(sqsh_ino->uid), &i_uid);
	if (err)
		return err;

	err = squashfs_get_id(sb, le16_to_cpu(sqsh_ino->guid), &i_gid);
	if (err)
		return err;

	i_uid_write(inode, i_uid);
	i_gid_write(inode, i_gid);
	inode->i_ino = le32_to_cpu(sqsh_ino->inode_number);
	inode->i_mtime.tv_sec = le32_to_cpu(sqsh_ino->mtime);
	inode->i_atime.tv_sec = inode->i_mtime.tv_sec;
	inode->i_ctime.tv_sec = inode->i_mtime.tv_sec;
	inode->i_mode = le16_to_cpu(sqsh_ino->mode);
	inode->i_size = 0;

	return err;
}