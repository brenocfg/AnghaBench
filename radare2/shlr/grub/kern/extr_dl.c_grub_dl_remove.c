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
typedef  scalar_t__ grub_dl_t ;
typedef  TYPE_1__* grub_dl_list_t ;
struct TYPE_4__ {scalar_t__ mod; struct TYPE_4__* next; } ;

/* Variables and functions */
 TYPE_1__* grub_dl_head ; 
 int /*<<< orphan*/  grub_free (TYPE_1__*) ; 

__attribute__((used)) static void
grub_dl_remove (grub_dl_t mod)
{
  grub_dl_list_t *p, q;

  for (p = &grub_dl_head, q = *p; q; p = &q->next, q = *p)
    if (q->mod == mod)
      {
	*p = q->next;
	grub_free (q);
	return;
      }
}