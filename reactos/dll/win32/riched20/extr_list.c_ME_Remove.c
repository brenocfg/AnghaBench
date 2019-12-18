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
struct TYPE_4__ {struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void ME_Remove(ME_DisplayItem *diWhere)
{
  ME_DisplayItem *diNext = diWhere->next;
  ME_DisplayItem *diPrev = diWhere->prev;
  assert(diNext);
  assert(diPrev);
  diPrev->next = diNext;
  diNext->prev = diPrev;
}