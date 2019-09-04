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
 int MAP_PRCMHIBRegRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCMHIBRegWrite (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RTC_MSEC_U32_REG_ADDR ; 

__attribute__((used)) static void RTCUseSet(void)
{
  unsigned int uiRegValue;

  uiRegValue = MAP_PRCMHIBRegRead(RTC_MSEC_U32_REG_ADDR) | (1 << 31);

  PRCMHIBRegWrite(RTC_MSEC_U32_REG_ADDR, uiRegValue);
}