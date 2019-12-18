#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS2_MOUSE_BTN_MASK ; 
 scalar_t__ X_IS_NEG ; 
 int /*<<< orphan*/  X_IS_OVF ; 
 scalar_t__ Y_IS_NEG ; 
 int /*<<< orphan*/  Y_IS_OVF ; 

__attribute__((used)) static inline void ps2_mouse_convert_report_to_hid(report_mouse_t *mouse_report) {
    // PS/2 mouse data is '9-bit integer'(-256 to 255) which is comprised of sign-bit and 8-bit value.
    // bit: 8    7 ... 0
    //      sign \8-bit/
    //
    // Meanwhile USB HID mouse indicates 8bit data(-127 to 127), note that -128 is not used.
    //
    // This converts PS/2 data into HID value. Use only -127-127 out of PS/2 9-bit.
    mouse_report->x = X_IS_NEG ? ((!X_IS_OVF && -127 <= mouse_report->x && mouse_report->x <= -1) ? mouse_report->x : -127) : ((!X_IS_OVF && 0 <= mouse_report->x && mouse_report->x <= 127) ? mouse_report->x : 127);
    mouse_report->y = Y_IS_NEG ? ((!Y_IS_OVF && -127 <= mouse_report->y && mouse_report->y <= -1) ? mouse_report->y : -127) : ((!Y_IS_OVF && 0 <= mouse_report->y && mouse_report->y <= 127) ? mouse_report->y : 127);

    // remove sign and overflow flags
    mouse_report->buttons &= PS2_MOUSE_BTN_MASK;

#ifdef PS2_MOUSE_INVERT_X
    mouse_report->x = -mouse_report->x;
#endif
#ifndef PS2_MOUSE_INVERT_Y  // NOTE if not!
    // invert coordinate of y to conform to USB HID mouse
    mouse_report->y = -mouse_report->y;
#endif
}