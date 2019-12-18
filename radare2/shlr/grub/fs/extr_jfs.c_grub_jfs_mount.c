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
struct grub_jfs_sblock {int dummy; } ;
struct grub_jfs_inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ magic; } ;
struct grub_jfs_data {TYPE_1__ fileset; int /*<<< orphan*/  disk; scalar_t__ linknest; scalar_t__ pos; TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ GRUB_ERR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  GRUB_JFS_FS1_INODE_BLK ; 
 int /*<<< orphan*/  GRUB_JFS_SBLOCK ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_jfs_data*) ; 
 struct grub_jfs_data* grub_malloc (int) ; 
 scalar_t__ grub_strncmp (char*,char*,int) ; 

__attribute__((used)) static struct grub_jfs_data *
grub_jfs_mount (grub_disk_t disk)
{
  struct grub_jfs_data *data = 0;

  data = grub_malloc (sizeof (struct grub_jfs_data));
  if (!data)
    return 0;

  /* Read the superblock.  */
  if (grub_disk_read (disk, GRUB_JFS_SBLOCK, 0,
		      sizeof (struct grub_jfs_sblock), &data->sblock))
    goto fail;

  if (grub_strncmp ((char *) (data->sblock.magic), "JFS1", 4))
    {
      grub_error (GRUB_ERR_BAD_FS, "not a JFS filesystem");
      goto fail;
    }

  data->disk = disk;
  data->pos = 0;
  data->linknest = 0;

  /* Read the inode of the first fileset.  */
  if (grub_disk_read (data->disk, GRUB_JFS_FS1_INODE_BLK, 0,
		      sizeof (struct grub_jfs_inode), &data->fileset))
    goto fail;

  return data;

 fail:
  grub_free (data);

  if (grub_errno == GRUB_ERR_OUT_OF_RANGE)
    grub_error (GRUB_ERR_BAD_FS, "not a JFS filesystem");

  return 0;
}