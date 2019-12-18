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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS31FL3731_set_value (int,int /*<<< orphan*/ ) ; 
 int LED_DRIVER_LED_COUNT ; 

void IS31FL3731_set_value_all(uint8_t value) {
    for (int i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        IS31FL3731_set_value(i, value);
    }
}