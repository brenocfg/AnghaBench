#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int buttons; int x; int y; int v; int h; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRESS_SCROLL_BUTTONS ; 
 int PS2_MOUSE_SCROLL_BTN_MASK ; 
 scalar_t__ PS2_MOUSE_SCROLL_BTN_SEND ; 
 int PS2_MOUSE_SCROLL_DIVISOR_H ; 
 int PS2_MOUSE_SCROLL_DIVISOR_V ; 
 int /*<<< orphan*/  RELEASE_SCROLL_BUTTONS ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  host_mouse_send (TYPE_1__*) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

__attribute__((used)) static inline void ps2_mouse_scroll_button_task(report_mouse_t *mouse_report) {
    static enum {
        SCROLL_NONE,
        SCROLL_BTN,
        SCROLL_SENT,
    } scroll_state                     = SCROLL_NONE;
    static uint16_t scroll_button_time = 0;

    if (PS2_MOUSE_SCROLL_BTN_MASK == (mouse_report->buttons & (PS2_MOUSE_SCROLL_BTN_MASK))) {
        // All scroll buttons are pressed

        if (scroll_state == SCROLL_NONE) {
            scroll_button_time = timer_read();
            scroll_state       = SCROLL_BTN;
        }

        // If the mouse has moved, update the report to scroll instead of move the mouse
        if (mouse_report->x || mouse_report->y) {
            scroll_state    = SCROLL_SENT;
            mouse_report->v = -mouse_report->y / (PS2_MOUSE_SCROLL_DIVISOR_V);
            mouse_report->h = mouse_report->x / (PS2_MOUSE_SCROLL_DIVISOR_H);
            mouse_report->x = 0;
            mouse_report->y = 0;
#ifdef PS2_MOUSE_INVERT_H
            mouse_report->h = -mouse_report->h;
#endif
#ifdef PS2_MOUSE_INVERT_V
            mouse_report->v = -mouse_report->v;
#endif
        }
    } else if (0 == (PS2_MOUSE_SCROLL_BTN_MASK & mouse_report->buttons)) {
        // None of the scroll buttons are pressed

#if PS2_MOUSE_SCROLL_BTN_SEND
        if (scroll_state == SCROLL_BTN && timer_elapsed(scroll_button_time) < PS2_MOUSE_SCROLL_BTN_SEND) {
            PRESS_SCROLL_BUTTONS;
            host_mouse_send(mouse_report);
            _delay_ms(100);
            RELEASE_SCROLL_BUTTONS;
        }
#endif
        scroll_state = SCROLL_NONE;
    }

    RELEASE_SCROLL_BUTTONS;
}