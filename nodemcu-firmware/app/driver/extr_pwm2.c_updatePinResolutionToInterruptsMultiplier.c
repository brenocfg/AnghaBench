#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int resolutionInterruptCounterMultiplier; int resolutionCPUTicks; } ;
typedef  TYPE_1__ pwm2_pin_setup_t ;

/* Variables and functions */

__attribute__((used)) static void updatePinResolutionToInterruptsMultiplier(pwm2_pin_setup_t *sPin, uint32_t timerCPUTicks) {
  sPin->resolutionInterruptCounterMultiplier = sPin->resolutionCPUTicks / timerCPUTicks;
}