#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int grub_ssize_t ;
typedef  int grub_size_t ;
typedef  TYPE_2__* grub_file_t ;
struct TYPE_6__ {scalar_t__ offset; scalar_t__ size; TYPE_1__* fs; } ;
struct TYPE_5__ {int (* read ) (TYPE_2__*,void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_2__*,void*,int) ; 

grub_ssize_t
grub_file_read (grub_file_t file, void *buf, grub_size_t len)
{
  grub_ssize_t res;

  if (file->offset > file->size)
    {
      grub_error (GRUB_ERR_OUT_OF_RANGE,
		  "attempt to read past the end of file");
      return -1;
    }

  if (len == 0 || len > file->size - file->offset)
    len = file->size - file->offset;

  /* Prevent an overflow.  */
  if ((grub_ssize_t) len < 0)
    len >>= 1;

  if (len == 0)
    return 0;

  res = (file->fs->read) (file, buf, len);
  if (res > 0)
    file->offset += res;

  return res;
}