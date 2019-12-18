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
 int /*<<< orphan*/  MP_HAL_PIN_MODE_INPUT ; 
 int /*<<< orphan*/  MP_HAL_PIN_PULL_UP ; 
 int /*<<< orphan*/  mp_hal_pin_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_pin_W23 ; 

void mboot_board_early_init(void) {
    // Enable 500mA on WBUS-DIP28
    mp_hal_pin_config(pyb_pin_W23, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_UP, 0);
}