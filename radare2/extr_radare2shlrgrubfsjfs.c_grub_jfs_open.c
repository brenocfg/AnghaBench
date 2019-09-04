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
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct grub_jfs_data {TYPE_2__ currinode; } ;
struct grub_file {int /*<<< orphan*/  size; struct grub_jfs_data* data; TYPE_1__* device; } ;
typedef  scalar_t__ grub_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 int GRUB_JFS_FILETYPE_MASK ; 
 int GRUB_JFS_FILETYPE_REG ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_jfs_data*) ; 
 int /*<<< orphan*/  grub_jfs_find_file (struct grub_jfs_data*,char const*) ; 
 struct grub_jfs_data* grub_jfs_mount (int /*<<< orphan*/ ) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_jfs_open (struct grub_file *file, const char *name)
{
  struct grub_jfs_data *data;

  grub_dl_ref (my_mod);

  data = grub_jfs_mount (file->device->disk);
  if (!data)
    goto fail;

  grub_jfs_find_file (data, name);
  if (grub_errno)
    goto fail;

  /* It is only possible for open regular files.  */
  if (! ((grub_le_to_cpu32 (data->currinode.mode)
	  & GRUB_JFS_FILETYPE_MASK) == GRUB_JFS_FILETYPE_REG))
    {
      grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a regular file");
      goto fail;
    }

  file->data = data;
  file->size = grub_le_to_cpu64 (data->currinode.size);

  return 0;

 fail:

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}