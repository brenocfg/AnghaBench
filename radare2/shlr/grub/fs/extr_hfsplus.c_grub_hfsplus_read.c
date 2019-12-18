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
struct grub_hfsplus_data {int /*<<< orphan*/  opened_file; } ;
typedef  int grub_ssize_t ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  TYPE_1__* grub_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  closure; int /*<<< orphan*/  read_hook; scalar_t__ data; } ;

/* Variables and functions */
 int grub_hfsplus_read_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static grub_ssize_t
grub_hfsplus_read (grub_file_t file, char *buf, grub_size_t len)
{
  struct grub_hfsplus_data *data =
    (struct grub_hfsplus_data *) file->data;

  int size = grub_hfsplus_read_file (&data->opened_file, file->read_hook,
				     file->closure, file->flags,
				     file->offset, len, buf);

  return size;
}