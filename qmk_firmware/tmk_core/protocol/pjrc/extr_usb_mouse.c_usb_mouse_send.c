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
typedef  scalar_t__ uint8_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_ENDPOINT ; 
 int RWAL ; 
 scalar_t__ SREG ; 
 scalar_t__ UDFNUML ; 
 int UEDATX ; 
 int UEINTX ; 
 int /*<<< orphan*/  UENUM ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  usb_configured () ; 
 scalar_t__ usb_mouse_protocol ; 

int8_t usb_mouse_send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons) {
    uint8_t intr_state, timeout;

    if (!usb_configured()) return -1;
    if (x == -128) x = -127;
    if (y == -128) y = -127;
    if (wheel_v == -128) wheel_v = -127;
    if (wheel_h == -128) wheel_h = -127;
    intr_state = SREG;
    cli();
    UENUM   = MOUSE_ENDPOINT;
    timeout = UDFNUML + 50;
    while (1) {
        // are we ready to transmit?
        if (UEINTX & (1 << RWAL)) break;
        SREG = intr_state;
        // has the USB gone offline?
        if (!usb_configured()) return -1;
        // have we waited too long?
        if (UDFNUML == timeout) return -1;
        // get ready to try checking again
        intr_state = SREG;
        cli();
        UENUM = MOUSE_ENDPOINT;
    }
    UEDATX = buttons;
    UEDATX = x;
    UEDATX = y;
    if (usb_mouse_protocol) {
        UEDATX = wheel_v;
        UEDATX = wheel_h;
    }

    UEINTX = 0x3A;
    SREG   = intr_state;
    return 0;
}