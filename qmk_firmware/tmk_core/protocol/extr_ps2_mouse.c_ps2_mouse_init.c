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
 int /*<<< orphan*/  PS2_MOUSE_INIT_DELAY ; 
 int /*<<< orphan*/  PS2_MOUSE_RECEIVE (char*) ; 
 int /*<<< orphan*/  PS2_MOUSE_RESET ; 
 int /*<<< orphan*/  PS2_MOUSE_SEND (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _delay_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_host_init () ; 
 int /*<<< orphan*/  ps2_mouse_enable_data_reporting () ; 
 int /*<<< orphan*/  ps2_mouse_enable_scrolling () ; 
 int /*<<< orphan*/  ps2_mouse_init_user () ; 
 int /*<<< orphan*/  ps2_mouse_set_remote_mode () ; 
 int /*<<< orphan*/  ps2_mouse_set_scaling_2_1 () ; 

void ps2_mouse_init(void) {
    ps2_host_init();

    _delay_ms(PS2_MOUSE_INIT_DELAY);  // wait for powering up

    PS2_MOUSE_SEND(PS2_MOUSE_RESET, "ps2_mouse_init: sending reset");

    PS2_MOUSE_RECEIVE("ps2_mouse_init: read BAT");
    PS2_MOUSE_RECEIVE("ps2_mouse_init: read DevID");

#ifdef PS2_MOUSE_USE_REMOTE_MODE
    ps2_mouse_set_remote_mode();
#else
    ps2_mouse_enable_data_reporting();
#endif

#ifdef PS2_MOUSE_ENABLE_SCROLLING
    ps2_mouse_enable_scrolling();
#endif

#ifdef PS2_MOUSE_USE_2_1_SCALING
    ps2_mouse_set_scaling_2_1();
#endif

    ps2_mouse_init_user();
}