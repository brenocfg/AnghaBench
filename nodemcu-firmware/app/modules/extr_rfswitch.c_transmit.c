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
struct TYPE_3__ {int high; int low; } ;
typedef  TYPE_1__ HighLow ;

/* Variables and functions */
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  platform_gpio_write (int,int) ; 

void transmit(HighLow pulses, bool invertedSignal, int pulseLength, int pin) {
  platform_gpio_write(pin, !invertedSignal);
  os_delay_us(pulseLength * pulses.high);
  platform_gpio_write(pin, invertedSignal);
  os_delay_us(pulseLength * pulses.low);
}