#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tailPtr; } ;
typedef  TYPE_3__ ptw32_srwl_rwlock_t ;
struct TYPE_10__ {TYPE_2__* wNodePtr; } ;
typedef  TYPE_4__ ptw32_srwl_local_t ;
struct TYPE_8__ {TYPE_1__* qNextPtr; } ;
struct TYPE_7__ {int /*<<< orphan*/  spin; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_PVOIDPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  PTW32_FALSE ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
ptw32_srwl_WriterUnlock(ptw32_srwl_rwlock_t* lockPtr, ptw32_srwl_local_t* localPtr)
{
  if (localPtr->wNodePtr->qNextPtr == NULL)
  {
    if (PTW32_INTERLOCKED_COMPARE_EXCHANGE_PTR(
              (PTW32_INTERLOCKED_PVOIDPTR)&lockPtr->tailPtr,
              (PTW32_INTERLOCKED_PVOID)NULL,
              (PTW32_INTERLOCKED_PVOID)localPtr->wNodePtr)
        == (PTW32_INTERLOCKED_PVOID)NULL)
    {
      return;
    }
    else
    {
      while (localPtr->wNodePtr->qNextPtr == NULL);
    }
  }
  /* Clean up */
  localPtr->wNodePtr->qNextPtr->spin = PTW32_FALSE;
  localPtr->wNodePtr->qNextPtr = NULL;
}