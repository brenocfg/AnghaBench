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
typedef  TYPE_1__* grub_dl_t ;
typedef  TYPE_2__* grub_dl_segment_t ;
struct TYPE_5__ {unsigned int section; void* addr; struct TYPE_5__* next; } ;
struct TYPE_4__ {TYPE_2__* segment; } ;

/* Variables and functions */

__attribute__((used)) static void *
grub_dl_get_section_addr (grub_dl_t mod, unsigned n)
{
  grub_dl_segment_t seg;

  for (seg = mod->segment; seg; seg = seg->next)
    if (seg->section == n)
      return seg->addr;

  return 0;
}