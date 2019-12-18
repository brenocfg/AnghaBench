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
 scalar_t__ HIB3P3_O_MEM_HIB_REG2 ; 
 unsigned long MAP_PRCMHIBRegRead (scalar_t__) ; 

unsigned long PRCMOCRRegisterRead(unsigned char ucIndex)
{
  //
  // Return the read value.
  //
  return MAP_PRCMHIBRegRead(HIB3P3_BASE+HIB3P3_O_MEM_HIB_REG2 + (ucIndex << 2));
}