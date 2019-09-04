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
struct grub_ntfs_data {scalar_t__ uuid; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_1__* grub_device_t ;
struct TYPE_3__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_ntfs_data*) ; 
 struct grub_ntfs_data* grub_ntfs_mount (int /*<<< orphan*/ ) ; 
 char* grub_xasprintf (char*,unsigned long long) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_ntfs_uuid (grub_device_t device, char **uuid)
{
  struct grub_ntfs_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_ntfs_mount (disk);
  if (data)
    {
      *uuid = grub_xasprintf ("%016llx", (unsigned long long) data->uuid);
    }
  else
    *uuid = NULL;

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}