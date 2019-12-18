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
struct stat_data {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; TYPE_3__ i_ctime; TYPE_2__ i_atime; TYPE_1__ i_mtime; int /*<<< orphan*/  i_nlink; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_attrs; } ;

/* Variables and functions */
 TYPE_4__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  SD_V2_SIZE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_atime (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_attrs (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_blocks (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_ctime (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_generation (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_gid (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_mode (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_mtime (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_nlink (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_rdev (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_size (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sd_v2_uid (struct stat_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_fake_used_blocks (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode2sd(void *sd, struct inode *inode, loff_t size)
{
	struct stat_data *sd_v2 = (struct stat_data *)sd;

	set_sd_v2_mode(sd_v2, inode->i_mode);
	set_sd_v2_nlink(sd_v2, inode->i_nlink);
	set_sd_v2_uid(sd_v2, i_uid_read(inode));
	set_sd_v2_size(sd_v2, size);
	set_sd_v2_gid(sd_v2, i_gid_read(inode));
	set_sd_v2_mtime(sd_v2, inode->i_mtime.tv_sec);
	set_sd_v2_atime(sd_v2, inode->i_atime.tv_sec);
	set_sd_v2_ctime(sd_v2, inode->i_ctime.tv_sec);
	set_sd_v2_blocks(sd_v2, to_fake_used_blocks(inode, SD_V2_SIZE));
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		set_sd_v2_rdev(sd_v2, new_encode_dev(inode->i_rdev));
	else
		set_sd_v2_generation(sd_v2, inode->i_generation);
	set_sd_v2_attrs(sd_v2, REISERFS_I(inode)->i_attrs);
}