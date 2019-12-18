#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_fat_data {int attr; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_1__* grub_device_t ;
struct TYPE_3__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 int GRUB_FAT_ATTR_DIRECTORY ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_fat_iterate_dir (int /*<<< orphan*/ ,struct grub_fat_data*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  grub_fat_label_hook ; 
 struct grub_fat_data* grub_fat_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_free (struct grub_fat_data*) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_fat_label (grub_device_t device, char **label)
{
  struct grub_fat_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_fat_mount (disk);
  if (! data)
    goto fail;

  if (! (data->attr & GRUB_FAT_ATTR_DIRECTORY))
    {
      grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a directory");
      return 0;
    }

  *label = 0;

  grub_fat_iterate_dir (disk, data, grub_fat_label_hook, label);

 fail:

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}