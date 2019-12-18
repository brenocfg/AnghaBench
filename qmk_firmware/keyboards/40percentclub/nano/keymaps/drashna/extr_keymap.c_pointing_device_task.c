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
struct TYPE_4__ {int /*<<< orphan*/  buttons; void* y; void* x; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_BTN1 ; 
 void* axisToMouseComponent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cursorTimeout ; 
 int /*<<< orphan*/  lastCursor ; 
 int /*<<< orphan*/  maxCursorSpeed ; 
 TYPE_1__ pointing_device_get_report () ; 
 int /*<<< orphan*/  pointing_device_send () ; 
 int /*<<< orphan*/  pointing_device_set_report (TYPE_1__) ; 
 int /*<<< orphan*/  readPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swPin ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  xOrigin ; 
 int /*<<< orphan*/  xPin ; 
 int /*<<< orphan*/  xPolarity ; 
 int /*<<< orphan*/  yOrigin ; 
 int /*<<< orphan*/  yPin ; 
 int /*<<< orphan*/  yPolarity ; 

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

    // todo read as one vector
    if (timer_elapsed(lastCursor) > cursorTimeout) {
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
        report.y   = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
    }
    //
    if (!readPin(swPin)) {
        report.buttons |= MOUSE_BTN1;
    } else {
        report.buttons &= ~MOUSE_BTN1;
    }

    pointing_device_set_report(report);
    pointing_device_send();
}