#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct grub_fb_data {scalar_t__ pri_size; scalar_t__ ofs; struct fbm_file* ptr; } ;
struct fbm_file {scalar_t__ data_start; } ;
typedef  int grub_uint32_t ;
typedef  int grub_ssize_t ;
typedef  int grub_size_t ;
typedef  TYPE_2__* grub_file_t ;
typedef  scalar_t__ grub_err_t ;
typedef  TYPE_3__* grub_disk_t ;
struct TYPE_9__ {scalar_t__ read_hook; int /*<<< orphan*/  closure; } ;
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/  flags; struct grub_fb_data* data; int /*<<< orphan*/  closure; scalar_t__ read_hook; TYPE_1__* device; } ;
struct TYPE_7__ {TYPE_3__* disk; } ;

/* Variables and functions */
 scalar_t__ grub_disk_read (TYPE_3__*,int,int,int,char*) ; 
 scalar_t__ grub_disk_read_ex (TYPE_3__*,scalar_t__,scalar_t__,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_ssize_t
grub_fbfs_read (grub_file_t file, char *buf, grub_size_t len)
{
  struct fbm_file *p;
  grub_disk_t disk;
  grub_uint32_t sector;
  grub_size_t saved_len, ofs;
  struct grub_fb_data *data;

  disk = file->device->disk;
  disk->read_hook = file->read_hook;
  disk->closure = file->closure;

  data = file->data;
  p = data->ptr;
  if (p->data_start >= data->pri_size)
    {
      grub_err_t err;

      err = grub_disk_read_ex (disk, p->data_start - data->ofs,
			       file->offset, len, buf, file->flags);
      disk->read_hook = 0;
      return (err) ? -1 : (grub_ssize_t) len;
    }

  sector = p->data_start + ((grub_uint32_t) file->offset / 510) - data->ofs;
  ofs = ((grub_uint32_t) file->offset % 510);
  saved_len = len;
  while (len)
    {
      int n;

      n = len;
      if (ofs + n > 510)
	n = 510 - ofs;
      if (grub_disk_read (disk, sector, ofs, n, buf))
	{
	  saved_len = -1;
	  break;
	}
      sector++;
      if (buf)
	buf += n;
      len -= n;
      ofs = 0;
    }

  disk->read_hook = 0;
  return saved_len;
}