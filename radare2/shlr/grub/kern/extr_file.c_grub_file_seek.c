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
typedef  scalar_t__ grub_off_t ;
typedef  TYPE_1__* grub_file_t ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 

grub_off_t
grub_file_seek (grub_file_t file, grub_off_t offset)
{
  grub_off_t old;

  if (offset > file->size)
    {
      grub_error (GRUB_ERR_OUT_OF_RANGE,
		  "attempt to seek outside of the file");
      return -1;
    }

  old = file->offset;
  file->offset = offset;
  return old;
}