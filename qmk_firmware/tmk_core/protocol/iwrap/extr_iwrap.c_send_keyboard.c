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
struct TYPE_3__ {int mods; int* keys; } ;
typedef  TYPE_1__ report_keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUX_FOOTER (int) ; 
 int /*<<< orphan*/  MUX_HEADER (int,int) ; 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 int /*<<< orphan*/  iwrap_connected () ; 
 int /*<<< orphan*/  xmit (int) ; 

__attribute__((used)) static void send_keyboard(report_keyboard_t *report) {
    if (!iwrap_connected() && !iwrap_check_connection()) return;
    MUX_HEADER(0x01, 0x0c);
    // HID raw mode header
    xmit(0x9f);
    xmit(0x0a);  // Length
    xmit(0xa1);  // DATA(Input)
    xmit(0x01);  // Report ID
    xmit(report->mods);
    xmit(0x00);  // reserved byte(always 0)
    xmit(report->keys[0]);
    xmit(report->keys[1]);
    xmit(report->keys[2]);
    xmit(report->keys[3]);
    xmit(report->keys[4]);
    xmit(report->keys[5]);
    MUX_FOOTER(0x01);
}