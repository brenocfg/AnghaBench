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
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  addr; struct TYPE_5__* next; } ;
struct TYPE_4__ {TYPE_2__* segment; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_arch_sync_caches (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  grub_dprintf (char*,char*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grub_dl_flush_cache (grub_dl_t mod)
{
  grub_dl_segment_t seg;

  for (seg = mod->segment; seg; seg = seg->next) {
    if (seg->size) {
      grub_dprintf ("modules", "flushing 0x%lx bytes at %p\n",
		    (unsigned long) seg->size, seg->addr);
      grub_arch_sync_caches (seg->addr, seg->size);
    }
  }
}