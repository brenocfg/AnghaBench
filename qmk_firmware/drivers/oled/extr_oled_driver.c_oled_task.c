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
 scalar_t__ OLED_SCROLL_TIMEOUT ; 
 scalar_t__ oled_active ; 
 scalar_t__ oled_dirty ; 
 int /*<<< orphan*/  oled_initialized ; 
 int /*<<< orphan*/  oled_off () ; 
 int /*<<< orphan*/  oled_render () ; 
 int /*<<< orphan*/  oled_scroll_left () ; 
 int /*<<< orphan*/  oled_scroll_off () ; 
 int /*<<< orphan*/  oled_scroll_right () ; 
 scalar_t__ oled_scroll_timeout ; 
 scalar_t__ oled_scrolling ; 
 int /*<<< orphan*/  oled_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oled_task_user () ; 
 scalar_t__ oled_timeout ; 
 scalar_t__ timer_expired32 (scalar_t__,scalar_t__) ; 
 scalar_t__ timer_read32 () ; 

void oled_task(void) {
    if (!oled_initialized) {
        return;
    }

    oled_set_cursor(0, 0);

    oled_task_user();

#if OLED_SCROLL_TIMEOUT > 0
    if (oled_dirty && oled_scrolling) {
        oled_scroll_timeout = timer_read32() + OLED_SCROLL_TIMEOUT;
        oled_scroll_off();
    }
#endif

    // Smart render system, no need to check for dirty
    oled_render();

    // Display timeout check
#if OLED_TIMEOUT > 0
    if (oled_active && timer_expired32(timer_read32(), oled_timeout)) {
        oled_off();
    }
#endif

#if OLED_SCROLL_TIMEOUT > 0
    if (!oled_scrolling && timer_expired32(timer_read32(), oled_scroll_timeout)) {
#    ifdef OLED_SCROLL_TIMEOUT_RIGHT
        oled_scroll_right();
#    else
        oled_scroll_left();
#    endif
    }
#endif
}