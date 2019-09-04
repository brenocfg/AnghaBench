#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ allocState; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ptw32_srwl_node_t ;
struct TYPE_6__ {TYPE_1__* rNodePtr; } ;
typedef  TYPE_2__ ptw32_srwl_local_t ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ptw32_srwl_free ; 
 scalar_t__ ptw32_srwl_in_use ; 

ptw32_srwl_node_t*
ptw32_srwl_AllocReaderNode(ptw32_srwl_local_t* local)
{
  ptw32_srwl_node_t* currNodePtr = local->rNodePtr;
  for (;;)
  {
    if (currNodePtr->allocState == ptw32_srwl_free)
    {
      if (PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
            (PTW32_INTERLOCKED_LONGPTR)&currNodePtr->allocState,
            (PTW32_INTERLOCKED_LONG)ptw32_srwl_in_use,
            (PTW32_INTERLOCKED_LONG)ptw32_srwl_free)
          == (PTW32_INTERLOCKED_LONG)ptw32_srwl_in_use)
      {
        return currNodePtr;
      }
    }
    currNodePtr = currNodePtr->next;
  }
}