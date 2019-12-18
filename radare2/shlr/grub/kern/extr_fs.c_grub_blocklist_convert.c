#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct read_blocklist_closure {scalar_t__ total_size; scalar_t__ blocks; int /*<<< orphan*/  part_start; scalar_t__ num; } ;
typedef  TYPE_3__* grub_file_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;
struct TYPE_10__ {scalar_t__ size; int flags; scalar_t__ offset; scalar_t__ data; TYPE_5__* fs; scalar_t__ read_hook; struct read_blocklist_closure* closure; TYPE_2__* device; } ;
struct TYPE_9__ {TYPE_1__* disk; } ;
struct TYPE_8__ {int /*<<< orphan*/  partition; } ;

/* Variables and functions */
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_file_read (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  grub_free (scalar_t__) ; 
 TYPE_5__ grub_fs_blocklist ; 
 int /*<<< orphan*/  grub_partition_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ read_blocklist ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
grub_blocklist_convert (grub_file_t file)
{
  struct read_blocklist_closure c;

  if ((file->fs == &grub_fs_blocklist) || (! file->device->disk) ||
      (! file->size))
    return;

  file->offset = 0;
  file->flags = 1;

  c.num = 0;
  c.blocks = 0;
  c.total_size = 0;
  c.part_start = grub_partition_get_start (file->device->disk->partition);
  file->read_hook = read_blocklist;
  file->closure = &c;
  grub_file_read (file, 0, file->size);
  file->read_hook = 0;
  if ((grub_errno) || (c.total_size != file->size))
    {
      grub_errno = 0;
      grub_free (c.blocks);
    }
  else
    {
      if (file->fs->close)
	(file->fs->close) (file);
      file->fs = &grub_fs_blocklist;
      file->data = c.blocks;
    }

  file->offset = 0;
}