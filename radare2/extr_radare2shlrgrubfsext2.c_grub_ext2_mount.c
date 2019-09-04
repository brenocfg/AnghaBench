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
struct grub_ext2_sblock {int dummy; } ;
struct TYPE_3__ {int ino; int inode_read; int /*<<< orphan*/  inode; struct grub_ext2_data* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  feature_incompat; int /*<<< orphan*/  magic; } ;
struct grub_ext2_data {int /*<<< orphan*/ * inode; TYPE_1__ diropen; int /*<<< orphan*/  disk; TYPE_2__ sblock; } ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int EXT2_DRIVER_IGNORED_INCOMPAT ; 
 int EXT2_DRIVER_SUPPORTED_INCOMPAT ; 
 scalar_t__ EXT2_MAGIC ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ GRUB_ERR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_ext2_read_inode (struct grub_ext2_data*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_free (struct grub_ext2_data*) ; 
 scalar_t__ grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 struct grub_ext2_data* grub_malloc (int) ; 

__attribute__((used)) static struct grub_ext2_data *
grub_ext2_mount (grub_disk_t disk)
{
  struct grub_ext2_data *data;

  data = grub_malloc (sizeof (struct grub_ext2_data));
  if (!data)
    return 0;

  /* Read the superblock.  */
  grub_disk_read (disk, 1 * 2, 0, sizeof (struct grub_ext2_sblock),
                  &data->sblock);
  if (grub_errno)
    goto fail;

  /* Make sure this is an ext2 filesystem.  */
  if (grub_le_to_cpu16 (data->sblock.magic) != EXT2_MAGIC)
    {
      grub_error (GRUB_ERR_BAD_FS, "not an ext2 filesystem");
      goto fail;
    }

  /* Check the FS doesn't have feature bits enabled that we don't support. */
  if (grub_le_to_cpu32 (data->sblock.feature_incompat)
        & ~(EXT2_DRIVER_SUPPORTED_INCOMPAT | EXT2_DRIVER_IGNORED_INCOMPAT))
    {
      grub_error (GRUB_ERR_BAD_FS, "filesystem has unsupported incompatible features");
      goto fail;
    }


  data->disk = disk;

  data->diropen.data = data;
  data->diropen.ino = 2;
  data->diropen.inode_read = 1;

  data->inode = &data->diropen.inode;

  grub_ext2_read_inode (data, 2, data->inode);
  if (grub_errno)
    goto fail;

  return data;

 fail:
  if (grub_errno == GRUB_ERR_OUT_OF_RANGE)
    grub_error (GRUB_ERR_BAD_FS, "not an ext2 filesystem");

  grub_free (data);
  return 0;
}