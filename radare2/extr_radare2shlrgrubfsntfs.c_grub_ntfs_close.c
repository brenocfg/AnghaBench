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
struct grub_ntfs_data {int /*<<< orphan*/  cmft; int /*<<< orphan*/  mmft; } ;
typedef  TYPE_1__* grub_file_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
struct TYPE_3__ {struct grub_ntfs_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_ntfs_data*) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_ntfs_close (grub_file_t file)
{
  struct grub_ntfs_data *data;

  data = file->data;

  if (data)
    {
      free_file (&data->mmft);
      free_file (&data->cmft);
      grub_free (data);
    }

  grub_dl_unref (my_mod);

  return grub_errno;
}