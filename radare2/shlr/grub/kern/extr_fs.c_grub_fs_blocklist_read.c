#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grub_ssize_t ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  TYPE_3__* grub_file_t ;
struct TYPE_8__ {TYPE_2__* device; int /*<<< orphan*/  closure; scalar_t__ read_hook; } ;
struct TYPE_7__ {TYPE_1__* disk; } ;
struct TYPE_6__ {scalar_t__ read_hook; int /*<<< orphan*/  closure; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_fs_blocklist_rw (int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_ssize_t
grub_fs_blocklist_read (grub_file_t file, char *buf, grub_size_t len)
{
  grub_ssize_t ret;
  file->device->disk->read_hook = file->read_hook;
  file->device->disk->closure = file->closure;
  ret = grub_fs_blocklist_rw (0, file, buf, len);
  file->device->disk->read_hook = 0;
  return ret;
}