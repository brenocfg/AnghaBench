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
typedef  int /*<<< orphan*/  SYS_CLK_INIT ;

/* Variables and functions */
 int /*<<< orphan*/  OSC_FRC_DIV_2 ; 
 int /*<<< orphan*/  OSC_ID_0 ; 
 int /*<<< orphan*/  PLIB_OSC_FRCDivisorSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_OSC_PBClockDivisorSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_DEVCON_SystemLock () ; 
 int /*<<< orphan*/  SYS_DEVCON_SystemUnlock () ; 

void SYS_CLK_Initialize(const SYS_CLK_INIT const *clkInit) {
  SYS_DEVCON_SystemUnlock();

  PLIB_OSC_FRCDivisorSelect(OSC_ID_0, OSC_FRC_DIV_2);

  /* Enable Peripheral Bus 1 */
  PLIB_OSC_PBClockDivisorSet(OSC_ID_0, 0, 1);

  SYS_DEVCON_SystemLock();
}