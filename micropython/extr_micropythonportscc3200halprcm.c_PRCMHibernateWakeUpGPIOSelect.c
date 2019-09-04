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
 scalar_t__ HIB3P3_O_MEM_GPIO_WAKE_CONF ; 
 unsigned long MAP_PRCMHIBRegRead (scalar_t__) ; 
 int /*<<< orphan*/  MAP_PRCMHIBRegWrite (scalar_t__,unsigned long) ; 

void PRCMHibernateWakeUpGPIOSelect(unsigned long ulGPIOBitMap, unsigned long ulType)
{
  unsigned char ucLoop;
  unsigned long ulRegValue;

  //
  // Shift the bits to extract the GPIO selection
  //
  ulGPIOBitMap >>= 16;

  //
  // Set the configuration for each GPIO
  //
  for(ucLoop=0; ucLoop < 7; ucLoop++)
  {
    if(ulGPIOBitMap & (1<<ucLoop))
    {
      ulRegValue  = MAP_PRCMHIBRegRead(HIB3P3_BASE+HIB3P3_O_MEM_GPIO_WAKE_CONF);
      ulRegValue |= (ulType << (ucLoop*2));
      MAP_PRCMHIBRegWrite(HIB3P3_BASE+HIB3P3_O_MEM_GPIO_WAKE_CONF, ulRegValue);
    }
  }
}