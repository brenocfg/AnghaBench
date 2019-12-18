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
struct inode {int i_size; int i_file_acl; scalar_t__ i_extra_isize; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_block; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_dtime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {scalar_t__ l_i_file_acl_high; } ;
struct TYPE_4__ {TYPE_1__ linux2; } ;
struct ext3_inode {int i_size; int i_file_acl_lo; scalar_t__ i_extra_isize; int /*<<< orphan*/ * i_block; int /*<<< orphan*/  i_dtime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; TYPE_2__ osd2; scalar_t__ i_size_high; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_links_count; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_flags; } ;
typedef  int loff_t ;
typedef  int ext4_fsblk_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ EXT3_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_inode_blocks (struct ext3_inode*,struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void Ext2DecodeInode(struct inode *dst, struct ext3_inode *src)
{
    dst->i_mode = src->i_mode;
    dst->i_flags = src->i_flags;
    dst->i_uid = src->i_uid;
    dst->i_gid = src->i_gid;
    dst->i_nlink = src->i_links_count;
    dst->i_generation = src->i_generation;
    dst->i_size = src->i_size;
    if (S_ISREG(src->i_mode)) {
        dst->i_size |= (loff_t)src->i_size_high << 32;
    }
    dst->i_file_acl = src->i_file_acl_lo;
    dst->i_file_acl |= (ext4_fsblk_t)src->osd2.linux2.l_i_file_acl_high << 32;
    dst->i_atime = src->i_atime;
    dst->i_ctime = src->i_ctime;
    dst->i_mtime = src->i_mtime;
    dst->i_dtime = src->i_dtime;
    dst->i_blocks = ext3_inode_blocks(src, dst);
    memcpy(&dst->i_block[0], &src->i_block[0], sizeof(__u32) * 15);
    if (EXT3_HAS_RO_COMPAT_FEATURE(dst->i_sb,
                                   EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE))
        dst->i_extra_isize = src->i_extra_isize;
    else
        dst->i_extra_isize = 0;
}