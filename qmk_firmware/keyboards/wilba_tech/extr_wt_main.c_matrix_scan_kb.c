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
 int /*<<< orphan*/  backlight_update_pwm_buffers () ; 
 int /*<<< orphan*/  matrix_scan_user () ; 

void matrix_scan_kb(void)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	// This only updates the LED driver buffers if something has changed.
	backlight_update_pwm_buffers();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	matrix_scan_user();
}