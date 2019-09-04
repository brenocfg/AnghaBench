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
typedef  TYPE_1__* grub_dl_list_t ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 TYPE_1__* grub_dl_head ; 
 scalar_t__ grub_dl_unload (int /*<<< orphan*/ ) ; 

void
grub_dl_unload_unneeded (void)
{
  /* Because grub_dl_remove modifies the list of modules, this
     implementation is tricky.  */
  grub_dl_list_t p = grub_dl_head;

  while (p)
    {
      if (grub_dl_unload (p->mod))
	{
	  p = grub_dl_head;
	  continue;
	}

      p = p->next;
    }
}