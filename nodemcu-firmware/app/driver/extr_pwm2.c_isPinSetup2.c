#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {TYPE_1__* pin; } ;
typedef  TYPE_2__ pwm2_interrupt_handler_data_t ;
struct TYPE_4__ {scalar_t__ gpioMask; } ;

/* Variables and functions */

__attribute__((used)) static inline bool isPinSetup2(const pwm2_interrupt_handler_data_t *data, const uint8_t pin) {
  return data->pin[pin].gpioMask > 0;
}