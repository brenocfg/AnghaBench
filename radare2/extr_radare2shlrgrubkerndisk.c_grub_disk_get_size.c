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
typedef  int /*<<< orphan*/  grub_uint64_t ;
typedef  TYPE_1__* grub_disk_t ;
struct TYPE_3__ {int /*<<< orphan*/  total_sectors; scalar_t__ partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_partition_get_len (scalar_t__) ; 

grub_uint64_t
grub_disk_get_size (grub_disk_t disk)
{
  if (disk->partition)
    return grub_partition_get_len (disk->partition);
  else
    return disk->total_sectors;
}