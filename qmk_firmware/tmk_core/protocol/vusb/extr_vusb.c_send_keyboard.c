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
typedef  int /*<<< orphan*/  report_keyboard_t ;

/* Variables and functions */
 int KBUF_SIZE ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/ * kbuf ; 
 int kbuf_head ; 
 int kbuf_tail ; 
 int /*<<< orphan*/  usbPoll () ; 
 int /*<<< orphan*/  vusb_transfer_keyboard () ; 

__attribute__((used)) static void send_keyboard(report_keyboard_t *report) {
    uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
    if (next != kbuf_tail) {
        kbuf[kbuf_head] = *report;
        kbuf_head       = next;
    } else {
        debug("kbuf: full\n");
    }

    // NOTE: send key strokes of Macro
    usbPoll();
    vusb_transfer_keyboard();
}