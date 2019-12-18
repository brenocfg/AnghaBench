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
 int /*<<< orphan*/  mp_hal_pin_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_pin_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pin_E14 ; 
 int /*<<< orphan*/  pin_E15 ; 

void STM32L476DISC_board_early_init(void) {
    // set SPI flash WP and HOLD pins high
    mp_hal_pin_output(pin_E14);
    mp_hal_pin_output(pin_E15);
    mp_hal_pin_write(pin_E14, 1);
    mp_hal_pin_write(pin_E15, 1);
}