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
typedef  TYPE_1__* grub_partition_t ;
typedef  int /*<<< orphan*/  grub_disk_addr_t ;
struct TYPE_3__ {scalar_t__ start; struct TYPE_3__* parent; } ;

/* Variables and functions */

__attribute__((used)) static inline grub_disk_addr_t
grub_partition_get_start (const grub_partition_t p)
{
  grub_partition_t part;
  grub_uint64_t part_start = 0;

  for (part = p; part; part = part->parent)
    part_start += part->start;

  return part_start;
}