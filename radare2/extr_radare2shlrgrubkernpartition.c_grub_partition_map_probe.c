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
struct find_func_closure {int partnum; scalar_t__ p; } ;
typedef  scalar_t__ grub_partition_t ;
typedef  TYPE_1__* grub_partition_map_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* iterate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_func_closure*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  find_func ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_free (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_func_closure*) ; 

__attribute__((used)) static grub_partition_t
grub_partition_map_probe (const grub_partition_map_t partmap,
			  grub_disk_t disk, int partnum)
{
  struct find_func_closure c;

  c.partnum = partnum;
  c.p = 0;
  partmap->iterate (disk, find_func, &c);
  if (grub_errno)
    goto fail;

  return c.p;

 fail:
  grub_free (c.p);
  return 0;
}