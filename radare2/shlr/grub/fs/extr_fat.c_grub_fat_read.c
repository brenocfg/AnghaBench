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
typedef  int /*<<< orphan*/  grub_ssize_t ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  TYPE_2__* grub_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  closure; int /*<<< orphan*/  read_hook; int /*<<< orphan*/  data; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_fat_read_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static grub_ssize_t
grub_fat_read (grub_file_t file, char *buf, grub_size_t len)
{
  return grub_fat_read_data (file->device->disk, file->data, file->read_hook,
			     file->closure, file->flags,
			     file->offset, len, buf);
}