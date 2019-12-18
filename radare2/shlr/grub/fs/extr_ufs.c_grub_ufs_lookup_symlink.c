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
struct TYPE_2__ {int /*<<< orphan*/  log2_blksz; } ;
struct grub_ufs_data {scalar_t__ linknest; int /*<<< orphan*/  be; TYPE_1__ sblock; int /*<<< orphan*/  disk; } ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_SYMLINK_LOOP ; 
 int GRUB_UFS_INODE ; 
 scalar_t__ GRUB_UFS_MAX_SYMLNK_CNT ; 
 scalar_t__ INODE (struct grub_ufs_data*,char*) ; 
 int INODE_DIRBLOCKS (struct grub_ufs_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ INODE_NBLOCKS (struct grub_ufs_data*) ; 
 size_t INODE_SIZE (struct grub_ufs_data*) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,char*) ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error (scalar_t__,char*,...) ; 
 char* grub_malloc (size_t) ; 
 int grub_num_to_cpu32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_strcpy (char*,char*) ; 
 int /*<<< orphan*/  grub_ufs_find_file (struct grub_ufs_data*,char*) ; 
 scalar_t__ grub_ufs_read_inode (struct grub_ufs_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_ufs_lookup_symlink (struct grub_ufs_data *data, int ino)
{
#ifndef _MSC_VER
  char symlink[INODE_SIZE (data)];
#else
  char * symlink = grub_malloc(INODE_SIZE (data));
#endif
  if (++data->linknest > GRUB_UFS_MAX_SYMLNK_CNT)
    return grub_error (GRUB_ERR_SYMLINK_LOOP, "too deep nesting of symlinks");

  if (INODE_NBLOCKS (data) == 0)
    grub_strcpy (symlink, (char *) INODE (data, symlink));
  else
    {
      grub_disk_read (data->disk,
		      (INODE_DIRBLOCKS (data, 0)
		       << grub_num_to_cpu32 (data->sblock.log2_blksz, 
					     data->be)),
		      0, INODE_SIZE (data), symlink);
      symlink[INODE_SIZE (data)] = '\0';
    }

  /* The symlink is an absolute path, go back to the root inode.  */
  if (symlink[0] == '/')
    ino = GRUB_UFS_INODE;

  /* Now load in the old inode.  */
  if (grub_ufs_read_inode (data, ino, 0))
    return grub_errno;

  grub_ufs_find_file (data, symlink);
  if (grub_errno)
    grub_error (grub_errno, "cannot follow symlink `%s'", symlink);

  return grub_errno;
}