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
 int /*<<< orphan*/  OSC_ID_0 ; 
 int /*<<< orphan*/  PLIB_OSC_SecondaryDisable (int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_OSC_SecondaryIsEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_DEVCON_SystemLock () ; 
 int /*<<< orphan*/  SYS_DEVCON_SystemUnlock () ; 

void SYS_CLK_SecondaryOscillatorDisable(void) {
  /* Check for secondary oscillator status */
  if (PLIB_OSC_SecondaryIsEnabled(OSC_ID_0)) {
    /* Unlock and disable secondary oscillator*/
    SYS_DEVCON_SystemUnlock();

    PLIB_OSC_SecondaryDisable(OSC_ID_0);

    SYS_DEVCON_SystemLock();
  }
}