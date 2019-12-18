#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  duty; } ;
typedef  TYPE_3__ pwm2_pin_setup_t ;
typedef  int /*<<< orphan*/  pwm2_pin_interrupt_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pin; } ;
struct TYPE_7__ {TYPE_3__* pin; } ;
struct TYPE_10__ {TYPE_2__ interruptData; TYPE_1__ setupData; } ;
typedef  TYPE_4__ pwm2_module_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  updatePinOffCounter (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void set_duty(pwm2_module_data_t *moduleData, const uint8_t pin, const uint32_t duty) {
  pwm2_pin_setup_t *sPin = &moduleData->setupData.pin[pin];
  pwm2_pin_interrupt_t *iPin = &moduleData->interruptData.pin[pin];
  sPin->duty = duty;
  updatePinOffCounter(iPin, sPin);
}