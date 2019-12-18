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
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  PAL_MODE_OUTPUT_PUSHPULL ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void led_init_ports() {
    // Set our LED pins as output
    palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL); // LED1
    palClearPad(GPIOB, 13);
    palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL); // LED2
    palClearPad(GPIOB, 14);
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); // LED3
    palClearPad(GPIOA, 8);
    palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL); // Capslock LED
    palClearPad(GPIOA, 0);
}