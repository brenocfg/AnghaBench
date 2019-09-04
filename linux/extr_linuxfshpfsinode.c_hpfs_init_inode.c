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
struct super_block {int dummy; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct inode {int i_size; int i_blocks; TYPE_3__ i_atime; TYPE_2__ i_mtime; TYPE_1__ i_ctime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct hpfs_inode_info {scalar_t__ i_dirty; int /*<<< orphan*/ * i_rddir_off; scalar_t__ i_ea_size; scalar_t__ i_ea_gid; scalar_t__ i_ea_uid; scalar_t__ i_ea_mode; scalar_t__ i_dsubdno; scalar_t__ i_dpos; scalar_t__ i_disk_sec; scalar_t__ i_file_sec; scalar_t__ i_n_secs; scalar_t__ i_dno; } ;
struct TYPE_8__ {int /*<<< orphan*/  sb_mode; int /*<<< orphan*/  sb_gid; int /*<<< orphan*/  sb_uid; } ;

/* Variables and functions */
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 TYPE_4__* hpfs_sb (struct super_block*) ; 

void hpfs_init_inode(struct inode *i)
{
	struct super_block *sb = i->i_sb;
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);

	i->i_uid = hpfs_sb(sb)->sb_uid;
	i->i_gid = hpfs_sb(sb)->sb_gid;
	i->i_mode = hpfs_sb(sb)->sb_mode;
	i->i_size = -1;
	i->i_blocks = -1;
	
	hpfs_inode->i_dno = 0;
	hpfs_inode->i_n_secs = 0;
	hpfs_inode->i_file_sec = 0;
	hpfs_inode->i_disk_sec = 0;
	hpfs_inode->i_dpos = 0;
	hpfs_inode->i_dsubdno = 0;
	hpfs_inode->i_ea_mode = 0;
	hpfs_inode->i_ea_uid = 0;
	hpfs_inode->i_ea_gid = 0;
	hpfs_inode->i_ea_size = 0;

	hpfs_inode->i_rddir_off = NULL;
	hpfs_inode->i_dirty = 0;

	i->i_ctime.tv_sec = i->i_ctime.tv_nsec = 0;
	i->i_mtime.tv_sec = i->i_mtime.tv_nsec = 0;
	i->i_atime.tv_sec = i->i_atime.tv_nsec = 0;
}