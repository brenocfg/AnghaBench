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
 int /*<<< orphan*/  oled_set_cursor (int,int) ; 
 int /*<<< orphan*/  render_icon () ; 
 int /*<<< orphan*/  render_keyboard_leds () ; 
 int /*<<< orphan*/  render_layer () ; 
 int /*<<< orphan*/  render_rgb_state () ; 

__attribute__((used)) static void render_status(void)
{
    render_icon();

    // Host Layer Status
    oled_set_cursor(6, 0);
    render_layer();

    // Host Keyboard LED Status
    oled_set_cursor(6, 1);
    render_keyboard_leds();

#ifdef RGB_ENABLE
    oled_set_cursor(6, 2);
    render_rgb_state();
#endif
}