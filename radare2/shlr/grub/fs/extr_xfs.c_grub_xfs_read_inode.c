#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grub_xfs_inode {scalar_t__ magic; } ;
struct TYPE_2__ {int log2_inode; } ;
struct grub_xfs_data {TYPE_1__ sblock; int /*<<< orphan*/  disk; } ;
typedef  int /*<<< orphan*/  grub_uint64_t ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct grub_xfs_inode*) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  grub_xfs_inode_block (struct grub_xfs_data*,int /*<<< orphan*/ ) ; 
 int grub_xfs_inode_offset (struct grub_xfs_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_xfs_read_inode (struct grub_xfs_data *data, grub_uint64_t ino,
		     struct grub_xfs_inode *inode)
{
  grub_uint64_t block = grub_xfs_inode_block (data, ino);
  int offset = grub_xfs_inode_offset (data, ino);

  /* Read the inode.  */
  if (grub_disk_read (data->disk, block, offset,
		      1 << data->sblock.log2_inode, inode))
    return grub_errno;

  if (grub_strncmp ((char *) inode->magic, "IN", 2))
    return grub_error (GRUB_ERR_BAD_FS, "not a correct XFS inode");

  return 0;
}