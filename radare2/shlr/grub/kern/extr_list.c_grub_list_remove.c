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
typedef  TYPE_1__* grub_list_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */

void
grub_list_remove (grub_list_t *head, grub_list_t item)
{
  grub_list_t *p, q;

  for (p = head, q = *p; q; p = &(q->next), q = q->next)
    if (q == item)
      {
	*p = q->next;
	break;
      }
}