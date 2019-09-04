#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grub_iso9660_data {int first_sector; TYPE_3__* disk; } ;
typedef  int grub_ssize_t ;
typedef  int grub_size_t ;
typedef  TYPE_1__* grub_file_t ;
struct TYPE_5__ {int /*<<< orphan*/ * read_hook; int /*<<< orphan*/  closure; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  closure; int /*<<< orphan*/ * read_hook; scalar_t__ data; } ;

/* Variables and functions */
 int GRUB_ISO9660_LOG2_BLKSZ ; 
 int /*<<< orphan*/  grub_disk_read_ex (TYPE_3__*,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ grub_errno ; 

__attribute__((used)) static grub_ssize_t
grub_iso9660_read (grub_file_t file, char *buf, grub_size_t len)
{
  struct grub_iso9660_data *data =
    (struct grub_iso9660_data *) file->data;

  /* XXX: The file is stored in as a single extent.  */
  data->disk->read_hook = file->read_hook;
  data->disk->closure = file->closure;
  grub_disk_read_ex (data->disk,
		     data->first_sector << GRUB_ISO9660_LOG2_BLKSZ,
		     file->offset,
		     len, buf, file->flags);
  data->disk->read_hook = NULL;

  if (grub_errno)
    return -1;

  return len;
}