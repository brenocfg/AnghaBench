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
struct TYPE_2__ {int /*<<< orphan*/  report; int /*<<< orphan*/  report_id; } ;
typedef  TYPE_1__ vusb_mouse_report_t ;
typedef  int /*<<< orphan*/  report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ID_MOUSE ; 
 scalar_t__ usbInterruptIsReady3 () ; 
 int /*<<< orphan*/  usbSetInterrupt3 (void*,int) ; 

__attribute__((used)) static void send_mouse(report_mouse_t *report) {
    vusb_mouse_report_t r = {.report_id = REPORT_ID_MOUSE, .report = *report};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&r, sizeof(vusb_mouse_report_t));
    }
}