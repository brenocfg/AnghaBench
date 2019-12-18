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
struct TYPE_4__ {scalar_t__ rtBaseTime; scalar_t__ rtIntervalTime; struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  SystemClockImpl ;
typedef  TYPE_1__ SystemClockAdviseEntry ;
typedef  scalar_t__ REFERENCE_TIME ;

/* Variables and functions */

__attribute__((used)) static void QUARTZ_InsertAviseEntryFromQueue(SystemClockImpl* This, SystemClockAdviseEntry* pEntry, SystemClockAdviseEntry** pQueue) {
  SystemClockAdviseEntry* prev_it = NULL;
  SystemClockAdviseEntry* it = NULL;
  REFERENCE_TIME bornTime =  pEntry->rtBaseTime + pEntry->rtIntervalTime;

  for (it = *pQueue; NULL != it && (it->rtBaseTime + it->rtIntervalTime) < bornTime; it = it->next) {
    prev_it = it;
  }
  if (NULL == prev_it) {
    pEntry->prev = NULL;
    if (NULL != (*pQueue)) pEntry->next = (*pQueue)->next;
    /*assert( NULL == pEntry->next->prev );*/
    if (NULL != pEntry->next) pEntry->next->prev = pEntry;
    (*pQueue) = pEntry;
  } else {
    pEntry->prev = prev_it;
    pEntry->next = prev_it->next;
    prev_it->next = pEntry;
    if (NULL != pEntry->next) pEntry->next->prev = pEntry;
  }
}