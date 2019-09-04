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
struct grub_ufs_sblock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;
struct grub_ufs_data {int be; TYPE_1__ sblock; scalar_t__ linknest; int /*<<< orphan*/  disk; } ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ GRUB_ERR_NONE ; 
 scalar_t__ GRUB_ERR_OUT_OF_RANGE ; 
 scalar_t__ GRUB_UFS_MAGIC ; 
 scalar_t__ grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_ufs_data*) ; 
 scalar_t__ grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 struct grub_ufs_data* grub_malloc (int) ; 
 int* sblocklist ; 

__attribute__((used)) static struct grub_ufs_data *
grub_ufs_mount (grub_disk_t disk)
{
  struct grub_ufs_data *data;
  int *sblklist = sblocklist;

  data = grub_malloc (sizeof (struct grub_ufs_data));
  if (!data)
    return 0;

  data->disk = disk;
  data->linknest = 0;
  /* Find a UFS sblock.  */
  while (*sblklist != -1)
    {
      grub_disk_read (disk, *sblklist, 0, sizeof (struct grub_ufs_sblock),
		      &data->sblock);
      if (grub_errno)
	goto fail;

      if (grub_le_to_cpu32 (data->sblock.magic) == GRUB_UFS_MAGIC)
	{
	  data->be = 0;
	  return data;
	}
      else if (grub_be_to_cpu32 (data->sblock.magic) == GRUB_UFS_MAGIC)
	{
	  data->be = 1;
	  return data;
	}
      sblklist++;
    }

 fail:

  if (grub_errno == GRUB_ERR_NONE || grub_errno == GRUB_ERR_OUT_OF_RANGE)
    {
#ifdef MODE_UFS2
      grub_error (GRUB_ERR_BAD_FS, "not an ufs2 filesystem");
#else
      grub_error (GRUB_ERR_BAD_FS, "not an ufs1 filesystem");
#endif
    }

  grub_free (data);

  return 0;
}