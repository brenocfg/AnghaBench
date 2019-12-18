#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_3__* pPeriodicAdvise; TYPE_3__* pSingleShotAdvise; } ;
struct TYPE_6__ {TYPE_3__* next; } ;
typedef  TYPE_2__ SystemClockImpl ;
typedef  TYPE_3__ SystemClockAdviseEntry ;

/* Variables and functions */

__attribute__((used)) static void QUARTZ_RemoveAviseEntryFromQueue(SystemClockImpl* This, SystemClockAdviseEntry* pEntry) {
  if (pEntry->prev) pEntry->prev->next = pEntry->next;
  if (pEntry->next) pEntry->next->prev = pEntry->prev;
  if (This->pSingleShotAdvise == pEntry) This->pSingleShotAdvise = pEntry->next;
  if (This->pPeriodicAdvise == pEntry)    This->pPeriodicAdvise = pEntry->next;
}