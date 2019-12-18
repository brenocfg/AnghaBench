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
 int /*<<< orphan*/  microbit_display_tick ; 
 int /*<<< orphan*/  ticker_register_low_pri_callback (int /*<<< orphan*/ ) ; 

void board_modules_init0(void) {
    ticker_register_low_pri_callback(microbit_display_tick);
}