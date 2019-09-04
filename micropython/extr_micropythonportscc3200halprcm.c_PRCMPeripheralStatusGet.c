#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int tBoolean ;
struct TYPE_2__ {scalar_t__ ulRstReg; } ;

/* Variables and functions */
 scalar_t__ ARCM_BASE ; 
 unsigned long HWREG (scalar_t__) ; 
 unsigned long PRCM_ENABLE_STATUS ; 
 TYPE_1__* PRCM_PeriphRegsList ; 

tBoolean PRCMPeripheralStatusGet(unsigned long ulPeripheral)
{
  unsigned long ReadyBit;

  //
  // Read the ready bit status
  //
  ReadyBit = HWREG(ARCM_BASE + PRCM_PeriphRegsList[ulPeripheral].ulRstReg);
  ReadyBit = ReadyBit & PRCM_ENABLE_STATUS;

  if (ReadyBit)
  {
    //
    // Module is ready
    //
    return(true);
  }
  else
  {
    //
    // Module is not ready
    //
    return(false);
  }
}