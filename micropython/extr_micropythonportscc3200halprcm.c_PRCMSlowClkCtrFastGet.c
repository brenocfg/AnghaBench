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

/* Variables and functions */
 scalar_t__ HIB1P2_BASE ; 
 scalar_t__ HIB1P2_O_HIB_RTC_TIMER_LSW_1P2 ; 
 scalar_t__ HIB1P2_O_HIB_RTC_TIMER_MSW_1P2 ; 
 unsigned long long HWREG (scalar_t__) ; 

unsigned long long PRCMSlowClkCtrFastGet(void)
{
  unsigned long long ullRTCVal;

  //
  // Read as 2 32-bit values
  //
  ullRTCVal = HWREG(HIB1P2_BASE + HIB1P2_O_HIB_RTC_TIMER_MSW_1P2);
  ullRTCVal = ullRTCVal << 32;
  ullRTCVal |= HWREG(HIB1P2_BASE + HIB1P2_O_HIB_RTC_TIMER_LSW_1P2);

  return ullRTCVal;

}