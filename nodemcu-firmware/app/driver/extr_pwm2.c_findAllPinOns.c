#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pin; } ;
typedef  TYPE_1__ pwm2_interrupt_handler_data_t ;

/* Variables and functions */
 int GPIO_PIN_NUM ; 
 int /*<<< orphan*/  computeIsPinOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isPinSetup2 (TYPE_1__*,int) ; 

__attribute__((used)) static inline uint16_t findAllPinOns(pwm2_interrupt_handler_data_t *data) {
  uint16_t maskOn = 0;
  for (int i = 1; i < GPIO_PIN_NUM; i++) {
    if (isPinSetup2(data, i)) {
      computeIsPinOn(&data->pin[i], &maskOn);
    }
  }
  return maskOn;
}