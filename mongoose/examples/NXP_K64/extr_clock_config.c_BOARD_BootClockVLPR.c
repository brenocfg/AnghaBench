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
struct TYPE_3__ {int /*<<< orphan*/  irclkEnableMode; int /*<<< orphan*/  ircs; int /*<<< orphan*/  fcrdiv; } ;
struct TYPE_4__ {int /*<<< orphan*/  coreClock; int /*<<< orphan*/  simConfig; TYPE_1__ mcgConfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BootToBlpiMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_SetSimConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLOCK_SetSimSafeDivs () ; 
 int /*<<< orphan*/  SMC ; 
 scalar_t__ SMC_GetPowerModeState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SetPowerModeProtection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SetPowerModeVlpr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SystemCoreClock ; 
 TYPE_2__ g_defaultClockConfigVlpr ; 
 int /*<<< orphan*/  kSMC_AllowPowerModeAll ; 
 scalar_t__ kSMC_PowerStateVlpr ; 

void BOARD_BootClockVLPR(void)
{
    CLOCK_SetSimSafeDivs();

    CLOCK_BootToBlpiMode(g_defaultClockConfigVlpr.mcgConfig.fcrdiv, g_defaultClockConfigVlpr.mcgConfig.ircs,
                         g_defaultClockConfigVlpr.mcgConfig.irclkEnableMode);

    CLOCK_SetSimConfig(&g_defaultClockConfigVlpr.simConfig);

    SystemCoreClock = g_defaultClockConfigVlpr.coreClock;

    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeVlpr(SMC, false);
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateVlpr)
    {
    }
}