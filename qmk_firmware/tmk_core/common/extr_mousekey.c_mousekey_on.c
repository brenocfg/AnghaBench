#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int y; int x; int v; int h; int /*<<< orphan*/  buttons; } ;

/* Variables and functions */
 scalar_t__ KC_MS_ACCEL0 ; 
 scalar_t__ KC_MS_ACCEL1 ; 
 scalar_t__ KC_MS_ACCEL2 ; 
 scalar_t__ KC_MS_BTN1 ; 
 scalar_t__ KC_MS_BTN2 ; 
 scalar_t__ KC_MS_BTN3 ; 
 scalar_t__ KC_MS_BTN4 ; 
 scalar_t__ KC_MS_BTN5 ; 
 scalar_t__ KC_MS_DOWN ; 
 scalar_t__ KC_MS_LEFT ; 
 scalar_t__ KC_MS_RIGHT ; 
 scalar_t__ KC_MS_UP ; 
 scalar_t__ KC_MS_WH_DOWN ; 
 scalar_t__ KC_MS_WH_LEFT ; 
 scalar_t__ KC_MS_WH_RIGHT ; 
 scalar_t__ KC_MS_WH_UP ; 
 int /*<<< orphan*/  MOUSE_BTN1 ; 
 int /*<<< orphan*/  MOUSE_BTN2 ; 
 int /*<<< orphan*/  MOUSE_BTN3 ; 
 int /*<<< orphan*/  MOUSE_BTN4 ; 
 int /*<<< orphan*/  MOUSE_BTN5 ; 
 TYPE_1__ mouse_report ; 
 int mousekey_accel ; 
 int move_unit () ; 
 int wheel_unit () ; 

void mousekey_on(uint8_t code) {
    if (code == KC_MS_UP)
        mouse_report.y = move_unit() * -1;
    else if (code == KC_MS_DOWN)
        mouse_report.y = move_unit();
    else if (code == KC_MS_LEFT)
        mouse_report.x = move_unit() * -1;
    else if (code == KC_MS_RIGHT)
        mouse_report.x = move_unit();
    else if (code == KC_MS_WH_UP)
        mouse_report.v = wheel_unit();
    else if (code == KC_MS_WH_DOWN)
        mouse_report.v = wheel_unit() * -1;
    else if (code == KC_MS_WH_LEFT)
        mouse_report.h = wheel_unit() * -1;
    else if (code == KC_MS_WH_RIGHT)
        mouse_report.h = wheel_unit();
    else if (code == KC_MS_BTN1)
        mouse_report.buttons |= MOUSE_BTN1;
    else if (code == KC_MS_BTN2)
        mouse_report.buttons |= MOUSE_BTN2;
    else if (code == KC_MS_BTN3)
        mouse_report.buttons |= MOUSE_BTN3;
    else if (code == KC_MS_BTN4)
        mouse_report.buttons |= MOUSE_BTN4;
    else if (code == KC_MS_BTN5)
        mouse_report.buttons |= MOUSE_BTN5;
    else if (code == KC_MS_ACCEL0)
        mousekey_accel |= (1 << 0);
    else if (code == KC_MS_ACCEL1)
        mousekey_accel |= (1 << 1);
    else if (code == KC_MS_ACCEL2)
        mousekey_accel |= (1 << 2);
}