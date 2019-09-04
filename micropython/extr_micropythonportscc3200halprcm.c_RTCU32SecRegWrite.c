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
 int /*<<< orphan*/  MAP_PRCMHIBRegWrite (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  RTC_SECS_U32_REG_ADDR ; 

__attribute__((used)) static void RTCU32SecRegWrite(unsigned long u32Msec)
{
  MAP_PRCMHIBRegWrite(RTC_SECS_U32_REG_ADDR, u32Msec);
}