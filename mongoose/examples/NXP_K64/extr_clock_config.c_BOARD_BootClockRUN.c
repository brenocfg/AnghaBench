#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fcrdiv; int /*<<< orphan*/  ircs; int /*<<< orphan*/  irclkEnableMode; int /*<<< orphan*/  pll0Config; int /*<<< orphan*/  oscsel; } ;
struct TYPE_4__ {int /*<<< orphan*/  coreClock; int /*<<< orphan*/  simConfig; TYPE_1__ mcgConfig; int /*<<< orphan*/  oscConfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_XTAL0_CLK_HZ ; 
 int /*<<< orphan*/  CLOCK_BootToPeeMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLOCK_InitOsc0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLOCK_SetInternalRefClkConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_SetSimConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLOCK_SetSimSafeDivs () ; 
 int /*<<< orphan*/  CLOCK_SetXtal0Freq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemCoreClock ; 
 TYPE_2__ g_defaultClockConfigRun ; 
 int /*<<< orphan*/  kMCG_PllClkSelPll0 ; 

void BOARD_BootClockRUN(void)
{
    CLOCK_SetSimSafeDivs();

    CLOCK_InitOsc0(&g_defaultClockConfigRun.oscConfig);
    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    CLOCK_BootToPeeMode(g_defaultClockConfigRun.mcgConfig.oscsel, kMCG_PllClkSelPll0,
                        &g_defaultClockConfigRun.mcgConfig.pll0Config);

    CLOCK_SetInternalRefClkConfig(g_defaultClockConfigRun.mcgConfig.irclkEnableMode,
                                  g_defaultClockConfigRun.mcgConfig.ircs, g_defaultClockConfigRun.mcgConfig.fcrdiv);

    CLOCK_SetSimConfig(&g_defaultClockConfigRun.simConfig);

    SystemCoreClock = g_defaultClockConfigRun.coreClock;
}