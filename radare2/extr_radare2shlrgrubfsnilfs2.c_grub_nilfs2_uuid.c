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
struct TYPE_4__ {int /*<<< orphan*/ * s_uuid; } ;
struct grub_nilfs2_data {TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_2__* grub_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_nilfs2_data*) ; 
 struct grub_nilfs2_data* grub_nilfs2_mount (int /*<<< orphan*/ ) ; 
 char* grub_xasprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_nilfs2_uuid (grub_device_t device, char **uuid)
{
  struct grub_nilfs2_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_nilfs2_mount (disk);
  if (data)
    {
      *uuid =
	grub_xasprintf
	("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%0x-%02x%02x%02x%02x%02x%02x",
	 data->sblock.s_uuid[0], data->sblock.s_uuid[1],
	 data->sblock.s_uuid[2], data->sblock.s_uuid[3],
	 data->sblock.s_uuid[4], data->sblock.s_uuid[5],
	 data->sblock.s_uuid[6], data->sblock.s_uuid[7],
	 data->sblock.s_uuid[8], data->sblock.s_uuid[9],
	 data->sblock.s_uuid[10], data->sblock.s_uuid[11],
	 data->sblock.s_uuid[12], data->sblock.s_uuid[13],
	 data->sblock.s_uuid[14], data->sblock.s_uuid[15]);
    }
  else
    *uuid = NULL;

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}