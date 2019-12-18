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
struct TYPE_4__ {int /*<<< orphan*/ * uuid; } ;
struct grub_reiserfs_data {TYPE_1__ superblock; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_2__* grub_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_reiserfs_data*) ; 
 struct grub_reiserfs_data* grub_reiserfs_mount (int /*<<< orphan*/ ) ; 
 char* grub_xasprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_reiserfs_uuid (grub_device_t device, char **uuid)
{
  struct grub_reiserfs_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_reiserfs_mount (disk);
  if (data)
    {
      *uuid = grub_xasprintf ("%04x%04x-%04x-%04x-%04x-%04x%04x%04x",
			     grub_be_to_cpu16 (data->superblock.uuid[0]),
			     grub_be_to_cpu16 (data->superblock.uuid[1]),
			     grub_be_to_cpu16 (data->superblock.uuid[2]),
			     grub_be_to_cpu16 (data->superblock.uuid[3]),
			     grub_be_to_cpu16 (data->superblock.uuid[4]),
			     grub_be_to_cpu16 (data->superblock.uuid[5]),
			     grub_be_to_cpu16 (data->superblock.uuid[6]),
			     grub_be_to_cpu16 (data->superblock.uuid[7]));
    }
  else
    *uuid = NULL;

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}