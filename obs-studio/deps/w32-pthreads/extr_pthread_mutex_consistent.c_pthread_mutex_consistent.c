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
typedef  TYPE_2__* pthread_mutex_t ;
struct TYPE_5__ {scalar_t__ kind; TYPE_1__* robustNode; } ;
struct TYPE_4__ {int /*<<< orphan*/  stateInconsistent; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_ROBUST_CONSISTENT ; 
 scalar_t__ PTW32_ROBUST_INCONSISTENT ; 

int
pthread_mutex_consistent (pthread_mutex_t* mutex)
{
  pthread_mutex_t mx = *mutex;
  int result = 0;

  /*
   * Let the system deal with invalid pointers.
   */
  if (mx == NULL)
    {
      return EINVAL;
    }

  if (mx->kind >= 0
        || (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_INCONSISTENT != PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
                                                (PTW32_INTERLOCKED_LONGPTR)&mx->robustNode->stateInconsistent,
                                                (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_CONSISTENT,
                                                (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_INCONSISTENT))
    {
      result = EINVAL;
    }

  return (result);
}