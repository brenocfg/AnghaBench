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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int MOUSEKEY_WHEEL_DELTA ; 
 int MOUSEKEY_WHEEL_MAX ; 
 int mk_wheel_max_speed ; 
 int mk_wheel_time_to_max ; 
 int mousekey_accel ; 
 int mousekey_repeat ; 

__attribute__((used)) static uint8_t wheel_unit(void) {
    uint16_t unit;
    if (mousekey_accel & (1 << 0)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed) / 4;
    } else if (mousekey_accel & (1 << 1)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed);
    } else if (mousekey_repeat == 0) {
        unit = MOUSEKEY_WHEEL_DELTA;
    } else if (mousekey_repeat >= mk_wheel_time_to_max) {
        unit = MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed;
    } else {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed * mousekey_repeat) / mk_wheel_time_to_max;
    }
    return (unit > MOUSEKEY_WHEEL_MAX ? MOUSEKEY_WHEEL_MAX : (unit == 0 ? 1 : unit));
}