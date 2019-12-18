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
 scalar_t__ HIB3P3_BASE ; 
 scalar_t__ HIB3P3_O_MEM_GPIO_WAKE_EN ; 
 scalar_t__ HIB3P3_O_MEM_HIB_RTC_WAKE_EN ; 
 unsigned long MAP_PRCMHIBRegRead (scalar_t__) ; 
 int /*<<< orphan*/  MAP_PRCMHIBRegWrite (scalar_t__,unsigned long) ; 

void PRCMHibernateWakeupSourceDisable(unsigned long ulHIBWakupSrc)
{
  unsigned long ulRegValue;

  //
  // Read the RTC register
  //
  ulRegValue = MAP_PRCMHIBRegRead(HIB3P3_BASE+HIB3P3_O_MEM_HIB_RTC_WAKE_EN);

  //
  // Disable the RTC as wakeup source if specified
  //
  ulRegValue &= ~(ulHIBWakupSrc & 0x1);

  //
  // Disable HIB wakeup sources
  //
  MAP_PRCMHIBRegWrite(HIB3P3_BASE+HIB3P3_O_MEM_HIB_RTC_WAKE_EN,ulRegValue);

  //
  // Read the GPIO wakeup configuration register
  //
  ulRegValue = MAP_PRCMHIBRegRead(HIB3P3_BASE+HIB3P3_O_MEM_GPIO_WAKE_EN);

  //
  // Enable the specified GPIOs a wakeup sources
  //
  ulRegValue &= ~((ulHIBWakupSrc>>16)&0xFF);

  //
  // Write the new register configuration
  //
  MAP_PRCMHIBRegWrite(HIB3P3_BASE+HIB3P3_O_MEM_GPIO_WAKE_EN,ulRegValue);
}