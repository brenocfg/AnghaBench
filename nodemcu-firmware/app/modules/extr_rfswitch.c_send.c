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
struct TYPE_3__ {int /*<<< orphan*/  invertedSignal; int /*<<< orphan*/  syncFactor; int /*<<< orphan*/  zero; int /*<<< orphan*/  one; } ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  platform_gpio_mode (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* proto ; 
 int /*<<< orphan*/  transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

void send(unsigned long protocol_id, unsigned long pulse_length, unsigned long repeat, unsigned long pin, unsigned long value, unsigned int length) {
  platform_gpio_mode(pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);
  Protocol p = proto[protocol_id-1];
  for (int nRepeat = 0; nRepeat < repeat; nRepeat++) {
    for (int i = length-1; i >= 0; i--) {
      if (value & (1L << i))
        transmit(p.one, p.invertedSignal, pulse_length, pin);
      else
        transmit(p.zero, p.invertedSignal, pulse_length, pin);
    }
    transmit(p.syncFactor, p.invertedSignal, pulse_length, pin);
  }
}