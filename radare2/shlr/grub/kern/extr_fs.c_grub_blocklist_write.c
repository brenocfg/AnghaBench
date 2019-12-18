#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int grub_ssize_t ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  TYPE_1__* grub_file_t ;
struct TYPE_4__ {int /*<<< orphan*/ * fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_fs_blocklist ; 
 int grub_fs_blocklist_rw (int,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

grub_ssize_t
grub_blocklist_write (grub_file_t file, const char *buf, grub_size_t len)
{
  return (file->fs != &grub_fs_blocklist) ? -1 :
    grub_fs_blocklist_rw (1, file, (char *) buf, len);
}