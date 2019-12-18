#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grub_fat_data {int attr; int /*<<< orphan*/  file_size; } ;
typedef  TYPE_2__* grub_file_t ;
typedef  scalar_t__ grub_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; struct grub_fat_data* data; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 scalar_t__ GRUB_ERR_NONE ; 
 int GRUB_FAT_ATTR_DIRECTORY ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 char* grub_fat_find_dir (int /*<<< orphan*/ ,struct grub_fat_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct grub_fat_data* grub_fat_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_free (struct grub_fat_data*) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_fat_open (grub_file_t file, const char *name)
{
  struct grub_fat_data *data = 0;
  char *p = (char *) name;

  grub_dl_ref (my_mod);

  data = grub_fat_mount (file->device->disk);
  if (! data)
    goto fail;

  do
    {
      p = grub_fat_find_dir (file->device->disk, data, p, 0, 0);
      if (grub_errno != GRUB_ERR_NONE)
	goto fail;
    }
  while (p);

  if (data->attr & GRUB_FAT_ATTR_DIRECTORY)
    {
      grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a file");
      goto fail;
    }

  file->data = data;
  file->size = data->file_size;

  return GRUB_ERR_NONE;

 fail:

  grub_free (data);

  grub_dl_unref (my_mod);

  return grub_errno;
}