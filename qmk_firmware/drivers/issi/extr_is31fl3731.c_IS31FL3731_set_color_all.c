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
 int DRIVER_LED_TOTAL ; 
 int /*<<< orphan*/  IS31FL3731_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IS31FL3731_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        IS31FL3731_set_color(i, red, green, blue);
    }
}