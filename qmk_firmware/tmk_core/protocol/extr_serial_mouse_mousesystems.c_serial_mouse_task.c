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
struct TYPE_4__ {void* y; void* x; int /*<<< orphan*/  buttons; void* v; void* h; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ report_mouse_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int16_t ;

/* Variables and functions */
 void* MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MOUSE_BTN1 ; 
 int /*<<< orphan*/  MOUSE_BTN2 ; 
 int /*<<< orphan*/  MOUSE_BTN3 ; 
 scalar_t__ debug_mouse ; 
 int /*<<< orphan*/  host_mouse_send (TYPE_1__*) ; 
 int /*<<< orphan*/  print_usb_data (TYPE_1__*) ; 
 int serial_recv2 () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void serial_mouse_task(void) {
    /* 5 byte ring buffer */
    static uint8_t buffer[5];
    static int     buffer_cur = 0;

    int16_t rcv;

    report_mouse_t report = {0, 0, 0, 0, 0};

    rcv = serial_recv2();
    if (rcv < 0) /* no new data */
        return;

    if (debug_mouse) xprintf("serial_mouse: byte: %04X\n", rcv);

    /*
     * Synchronization: mouse(4) says that all
     * bytes but the first one in the packet have
     * bit 7 == 0, but this is untrue.
     * Therefore we discard all bytes up to the
     * first one with the characteristic bit pattern.
     */
    if (buffer_cur == 0 && (rcv >> 3) != 0x10) return;

    buffer[buffer_cur++] = (uint8_t)rcv;

    if (buffer_cur < 5) return;
    buffer_cur = 0;

#ifdef SERIAL_MOUSE_CENTER_SCROLL
    if ((buffer[0] & 0x7) == 0x5 && (buffer[1] || buffer[2])) {
        /* USB HID uses only values from -127 to 127 */
        report.h = MAX((int8_t)buffer[1], -127);
        report.v = MAX((int8_t)buffer[2], -127);

        print_usb_data(&report);
        host_mouse_send(&report);

        if (buffer[3] || buffer[4]) {
            report.h = MAX((int8_t)buffer[3], -127);
            report.v = MAX((int8_t)buffer[4], -127);

            print_usb_data(&report);
            host_mouse_send(&report);
        }

        return;
    }
#endif

    /*
     * parse 5 byte packet.
     * NOTE: We only get a complete packet
     * if the mouse moved or the button states
     * change.
     */
    if (!(buffer[0] & (1 << 2))) report.buttons |= MOUSE_BTN1;
    if (!(buffer[0] & (1 << 1))) report.buttons |= MOUSE_BTN3;
    if (!(buffer[0] & (1 << 0))) report.buttons |= MOUSE_BTN2;

    /* USB HID uses only values from -127 to 127 */
    report.x = MAX((int8_t)buffer[1], -127);
    report.y = MAX(-(int8_t)buffer[2], -127);

    print_usb_data(&report);
    host_mouse_send(&report);

    if (buffer[3] || buffer[4]) {
        report.x = MAX((int8_t)buffer[3], -127);
        report.y = MAX(-(int8_t)buffer[4], -127);

        print_usb_data(&report);
        host_mouse_send(&report);
    }
}