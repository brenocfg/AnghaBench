#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_SIZEPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_SIZE ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 

void 
ptw32_mcs_flag_set (HANDLE * flag)
{
  HANDLE e = (HANDLE)(PTW32_INTERLOCKED_SIZE)PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE(
						(PTW32_INTERLOCKED_SIZEPTR)flag,
						(PTW32_INTERLOCKED_SIZE)-1,
						(PTW32_INTERLOCKED_SIZE)0);
  if ((HANDLE)0 != e)
    {
      /* another thread has already stored an event handle in the flag */
      SetEvent(e);
    }
}