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
struct TYPE_4__ {scalar_t__ uuidhi; scalar_t__ uuidlow; } ;
struct grub_ufs_data {TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_2__* grub_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_ufs_data*) ; 
 scalar_t__ grub_le_to_cpu32 (scalar_t__) ; 
 struct grub_ufs_data* grub_ufs_mount (int /*<<< orphan*/ ) ; 
 char* grub_xasprintf (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_ufs_uuid (grub_device_t device, char **uuid)
{
  struct grub_ufs_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_ufs_mount (disk);
  if (data && (data->sblock.uuidhi != 0 || data->sblock.uuidlow != 0))
    *uuid = grub_xasprintf ("%08x%08x",
			   (unsigned) grub_le_to_cpu32 (data->sblock.uuidhi),
			   (unsigned) grub_le_to_cpu32 (data->sblock.uuidlow));
  else
    *uuid = NULL;

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}