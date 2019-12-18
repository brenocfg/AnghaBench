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
struct TYPE_2__ {int x; int y; int v; int h; } ;

/* Variables and functions */
 scalar_t__ UINT8_MAX ; 
 int /*<<< orphan*/  last_timer ; 
 int mk_delay ; 
 int mk_interval ; 
 TYPE_1__ mouse_report ; 
 scalar_t__ mousekey_repeat ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int move_unit () ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 void* times_inv_sqrt2 (int) ; 
 int wheel_unit () ; 

void mousekey_task(void) {
    if (timer_elapsed(last_timer) < (mousekey_repeat ? mk_interval : mk_delay * 10)) {
        return;
    }
    if (mouse_report.x == 0 && mouse_report.y == 0 && mouse_report.v == 0 && mouse_report.h == 0) {
        return;
    }
    if (mousekey_repeat != UINT8_MAX) mousekey_repeat++;
    if (mouse_report.x > 0) mouse_report.x = move_unit();
    if (mouse_report.x < 0) mouse_report.x = move_unit() * -1;
    if (mouse_report.y > 0) mouse_report.y = move_unit();
    if (mouse_report.y < 0) mouse_report.y = move_unit() * -1;
    /* diagonal move [1/sqrt(2)] */
    if (mouse_report.x && mouse_report.y) {
        mouse_report.x = times_inv_sqrt2(mouse_report.x);
        if (mouse_report.x == 0) {
            mouse_report.x = 1;
        }
        mouse_report.y = times_inv_sqrt2(mouse_report.y);
        if (mouse_report.y == 0) {
            mouse_report.y = 1;
        }
    }
    if (mouse_report.v > 0) mouse_report.v = wheel_unit();
    if (mouse_report.v < 0) mouse_report.v = wheel_unit() * -1;
    if (mouse_report.h > 0) mouse_report.h = wheel_unit();
    if (mouse_report.h < 0) mouse_report.h = wheel_unit() * -1;
    mousekey_send();
}