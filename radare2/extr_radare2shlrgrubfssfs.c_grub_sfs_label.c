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
struct grub_sfs_data {char* label; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_1__* grub_device_t ;
struct TYPE_3__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_sfs_data*) ; 
 struct grub_sfs_data* grub_sfs_mount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_sfs_label (grub_device_t device, char **label)
{
  struct grub_sfs_data *data;
  grub_disk_t disk = device->disk;

  data = grub_sfs_mount (disk);
  if (data)
    *label = data->label;

  grub_free (data);

  return grub_errno;
}