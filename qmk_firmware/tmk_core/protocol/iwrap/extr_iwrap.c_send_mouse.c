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
struct TYPE_3__ {int buttons; int x; int y; int v; int h; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUX_FOOTER (int) ; 
 int /*<<< orphan*/  MUX_HEADER (int,int) ; 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 int /*<<< orphan*/  iwrap_connected () ; 
 int /*<<< orphan*/  xmit (int) ; 

__attribute__((used)) static void send_mouse(report_mouse_t *report) {
#if defined(MOUSEKEY_ENABLE) || defined(PS2_MOUSE_ENABLE) || defined(POINTING_DEVICE_ENABLE)
    if (!iwrap_connected() && !iwrap_check_connection()) return;
    MUX_HEADER(0x01, 0x09);
    // HID raw mode header
    xmit(0x9f);
    xmit(0x07);  // Length
    xmit(0xa1);  // DATA(Input)
    xmit(0x02);  // Report ID
    xmit(report->buttons);
    xmit(report->x);
    xmit(report->y);
    xmit(report->v);
    xmit(report->h);
    MUX_FOOTER(0x01);
#endif
}