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
struct TYPE_4__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  mtime2; } ;
struct grub_ufs_data {int /*<<< orphan*/  be; TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  grub_int32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_2__* grub_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_ufs_data*) ; 
 int /*<<< orphan*/  grub_num_to_cpu32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_num_to_cpu64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct grub_ufs_data* grub_ufs_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_ufs_mtime (grub_device_t device, grub_int32_t *tm)
{
  struct grub_ufs_data *data = 0;

  grub_dl_ref (my_mod);

  data = grub_ufs_mount (device->disk);
  if (!data)
    *tm = 0;
  else
#ifdef MODE_UFS2
    *tm = grub_num_to_cpu64 (data->sblock.mtime2, data->be);
#else
    *tm = grub_num_to_cpu32 (data->sblock.mtime, data->be);
#endif

  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}