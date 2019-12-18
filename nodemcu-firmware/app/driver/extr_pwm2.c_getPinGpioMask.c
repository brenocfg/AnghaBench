#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int GPIO_ID_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pin_num ; 

__attribute__((used)) static uint16_t getPinGpioMask(uint8_t pin) {
  return 1 << GPIO_ID_PIN(pin_num[pin]);
}