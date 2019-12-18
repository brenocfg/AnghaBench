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
 int BOOTMAGIC_LITE_COLUMN ; 
 int /*<<< orphan*/  BOOTMAGIC_LITE_ROW ; 
 int DEBOUNCE ; 
 int DEBOUNCING_DELAY ; 
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  eeconfig_disable () ; 
 int matrix_get_row (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_scan () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

__attribute__((weak)) void bootmagic_lite(void) {
    // The lite version of TMK's bootmagic based on Wilba.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
#if defined(DEBOUNCING_DELAY) && DEBOUNCING_DELAY > 0
    wait_ms(DEBOUNCING_DELAY * 2);
#elif defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();

    // If the Esc and space bar are held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // Assumes Esc is at [0,0].
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        eeconfig_disable();
        // Jump to bootloader.
        bootloader_jump();
    }
}