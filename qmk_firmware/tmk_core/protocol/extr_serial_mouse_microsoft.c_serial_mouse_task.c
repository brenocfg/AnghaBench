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
typedef  int uint8_t ;
struct TYPE_4__ {int x; int y; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ report_mouse_t ;
typedef  int int16_t ;

/* Variables and functions */
 void* MAX (int,int) ; 
 int /*<<< orphan*/  MOUSE_BTN1 ; 
 int /*<<< orphan*/  MOUSE_BTN2 ; 
 int /*<<< orphan*/  MOUSE_BTN3 ; 
 scalar_t__ debug_mouse ; 
 int /*<<< orphan*/  host_mouse_send (TYPE_1__*) ; 
 int /*<<< orphan*/  print_usb_data (TYPE_1__*) ; 
 int serial_recv2 () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void serial_mouse_task(void) {
    /* 3 byte ring buffer */
    static uint8_t buffer[3];
    static int     buffer_cur = 0;

    static report_mouse_t report = {};

    int16_t rcv;

    rcv = serial_recv2();
    if (rcv < 0) /* no new data */
        return;

    if (debug_mouse) xprintf("serial_mouse: byte: %04X\n", rcv);

    /*
     * If bit 6 is one, this signals the beginning
     * of a 3 byte sequence/packet.
     */
    if (rcv & (1 << 6)) buffer_cur = 0;

    buffer[buffer_cur] = (uint8_t)rcv;

    if (buffer_cur == 0 && buffer[buffer_cur] == 0x20) {
        /*
         * Logitech extension: This must be a follow-up on
         * the last 3-byte packet signaling a middle button click
         */
        report.buttons |= MOUSE_BTN3;
        report.x = report.y = 0;

        print_usb_data(&report);
        host_mouse_send(&report);
        return;
    }

    buffer_cur++;

    if (buffer_cur < 3) return;
    buffer_cur = 0;

    /*
     * parse 3 byte packet.
     * NOTE: We only get a complete packet
     * if the mouse moved or the button states
     * change.
     */
    report.buttons = 0;
    if (buffer[0] & (1 << 5)) report.buttons |= MOUSE_BTN1;
    if (buffer[0] & (1 << 4)) report.buttons |= MOUSE_BTN2;

    report.x = (buffer[0] << 6) | buffer[1];
    report.y = ((buffer[0] << 4) & 0xC0) | buffer[2];

    /* USB HID uses values from -127 to 127 only */
    report.x = MAX(report.x, -127);
    report.y = MAX(report.y, -127);

#if 0
    if (!report.buttons && !report.x && !report.y) {
        /*
         * Microsoft extension: Middle mouse button pressed
         * FIXME: I don't know how exactly this extension works.
         */
        report.buttons |= MOUSE_BTN3;
    }
#endif

    print_usb_data(&report);
    host_mouse_send(&report);
}