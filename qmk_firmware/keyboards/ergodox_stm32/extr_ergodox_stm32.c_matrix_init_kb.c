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

/* Variables and functions */
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  PAL_MODE_OUTPUT_PUSHPULL ; 
 int /*<<< orphan*/  ergodox_blink_all_leds () ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void matrix_init_kb(void)
{
    // Init LED Ports
    palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL); // LED 1
    palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL); // LED 2
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); // LED 3

    ergodox_blink_all_leds();

    matrix_init_user();
}