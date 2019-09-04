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
 int /*<<< orphan*/  MAP_PRCMHIBRegWrite (scalar_t__,unsigned long) ; 

void PRCMOCRRegisterWrite(unsigned char ucIndex, unsigned long ulRegValue)
{
  MAP_PRCMHIBRegWrite(HIB3P3_BASE+HIB3P3_O_MEM_HIB_REG2+(ucIndex << 2),ulRegValue);
}