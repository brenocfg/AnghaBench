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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int currentInterruptCounter; int pulseInterruptCcounter; int offInterruptCounter; int /*<<< orphan*/  gpioMask; } ;
typedef  TYPE_1__ pwm2_pin_interrupt_t ;

/* Variables and functions */

__attribute__((used)) static inline void computeIsPinOn(pwm2_pin_interrupt_t *pin, uint16_t *maskOn) {
  if (pin->currentInterruptCounter == pin->pulseInterruptCcounter) {
    pin->currentInterruptCounter = 1;
  } else {
    pin->currentInterruptCounter++;
  }
  // ets_printf("curr=%u    on=%u\n", pin->currentInterruptCounter, (pin->currentInterruptCounter < pin->offInterruptCounter));
  if (pin->currentInterruptCounter < pin->offInterruptCounter) {
    *maskOn |= pin->gpioMask;
  }
}