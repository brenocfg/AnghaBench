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
typedef  TYPE_2__* grub_dl_list_t ;
struct TYPE_5__ {TYPE_1__* mod; struct TYPE_5__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 TYPE_2__* grub_dl_head ; 
 int /*<<< orphan*/  grub_dl_unload_unneeded () ; 

void
grub_dl_unload_all (void)
{
  while (grub_dl_head)
    {
      grub_dl_list_t p;

      grub_dl_unload_unneeded ();

      /* Force to decrement the ref count. This will purge pre-loaded
	 modules and manually inserted modules.  */
      for (p = grub_dl_head; p; p = p->next)
	p->mod->ref_count--;
    }
}