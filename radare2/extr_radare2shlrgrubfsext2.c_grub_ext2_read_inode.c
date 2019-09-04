#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct grub_ext2_sblock {int /*<<< orphan*/  inodes_per_group; } ;
struct grub_ext2_inode {int dummy; } ;
struct grub_ext2_data {int /*<<< orphan*/  disk; struct grub_ext2_sblock sblock; } ;
struct grub_ext2_block_group {int /*<<< orphan*/  inode_table_id; } ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int EXT2_BLOCK_SIZE (struct grub_ext2_data*) ; 
 unsigned int EXT2_INODE_SIZE (struct grub_ext2_data*) ; 
 scalar_t__ GRUB_ERR_BAD_FS ; 
 unsigned int LOG2_EXT2_BLOCK_SIZE (struct grub_ext2_data*) ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,unsigned int,unsigned int,int,struct grub_ext2_inode*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_ext2_blockgroup (struct grub_ext2_data*,int,struct grub_ext2_block_group*) ; 
 unsigned int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_ext2_read_inode (struct grub_ext2_data *data,
		      int ino, struct grub_ext2_inode *inode)
{
  struct grub_ext2_block_group blkgrp;
  struct grub_ext2_sblock *sblock = &data->sblock;
  int inodes_per_block;
  unsigned int blkno;
  unsigned int blkoff;

  /* It is easier to calculate if the first inode is 0.  */
  ino--;
  int div = grub_le_to_cpu32 (sblock->inodes_per_group);
  if (div < 1) {
    return grub_errno = GRUB_ERR_BAD_FS;
  }
  grub_ext2_blockgroup (data, ino / div, &blkgrp);
  if (grub_errno)
    return grub_errno;

  int inode_size = EXT2_INODE_SIZE (data);
  if (inode_size < 1) {
    return grub_errno = GRUB_ERR_BAD_FS;
  }
  inodes_per_block = EXT2_BLOCK_SIZE (data) / inode_size;
  if (inodes_per_block < 1) {
    return grub_errno = GRUB_ERR_BAD_FS;
  }
  blkno = (ino % grub_le_to_cpu32 (sblock->inodes_per_group))
    / inodes_per_block;
  blkoff = (ino % grub_le_to_cpu32 (sblock->inodes_per_group))
    % inodes_per_block;

  /* Read the inode.  */
  if (grub_disk_read (data->disk,
		      ((grub_le_to_cpu32 (blkgrp.inode_table_id) + blkno)
		        << LOG2_EXT2_BLOCK_SIZE (data)),
		      EXT2_INODE_SIZE (data) * blkoff,
		      sizeof (struct grub_ext2_inode), inode))
    return grub_errno;

  return 0;
}