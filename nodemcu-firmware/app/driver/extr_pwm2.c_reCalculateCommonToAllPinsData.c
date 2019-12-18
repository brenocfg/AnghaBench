#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pin; int /*<<< orphan*/  interruptTimerCPUTicks; int /*<<< orphan*/  interruptTimerTicks; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pin; int /*<<< orphan*/  enabledGpioMask; } ;
struct TYPE_10__ {TYPE_2__ setupData; TYPE_1__ interruptData; } ;
typedef  TYPE_3__ pwm2_module_data_t ;

/* Variables and functions */
 int GPIO_PIN_NUM ; 
 int /*<<< orphan*/  cpuToTimerTicks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findAllEnabledGpioMask (TYPE_3__*) ; 
 int /*<<< orphan*/  findCommonCPUTicksDivisor (TYPE_3__*) ; 
 scalar_t__ isPinSetup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  updatePinOffCounter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updatePinPulseToInterruptsCounter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updatePinResolutionToInterruptsMultiplier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reCalculateCommonToAllPinsData(pwm2_module_data_t *moduleData) {
  moduleData->interruptData.enabledGpioMask = findAllEnabledGpioMask(moduleData);
  moduleData->setupData.interruptTimerCPUTicks = findCommonCPUTicksDivisor(moduleData);
  moduleData->setupData.interruptTimerTicks = cpuToTimerTicks(moduleData->setupData.interruptTimerCPUTicks);
  for (int i = 1; i < GPIO_PIN_NUM; i++) {
    if (isPinSetup(moduleData, i)) {
      updatePinResolutionToInterruptsMultiplier(&moduleData->setupData.pin[i], moduleData->setupData.interruptTimerCPUTicks);
      updatePinPulseToInterruptsCounter(&moduleData->interruptData.pin[i], &moduleData->setupData.pin[i]);
      updatePinOffCounter(&moduleData->interruptData.pin[i], &moduleData->setupData.pin[i]);
    }
  }
}