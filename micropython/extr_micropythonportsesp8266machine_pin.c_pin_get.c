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
typedef  int uint ;

/* Variables and functions */
 int GPIO_INPUT_GET (int) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_GPIO_IN_DATA ; 

int pin_get(uint pin) {
    if (pin == 16) {
        return READ_PERI_REG(RTC_GPIO_IN_DATA) & 1;
    }
    return GPIO_INPUT_GET(pin);
}