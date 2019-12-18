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
typedef  int uint16_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRA_ENDPOINT ; 
 int RWAL ; 
 scalar_t__ SREG ; 
 scalar_t__ UDFNUML ; 
 int UEDATX ; 
 int UEINTX ; 
 int /*<<< orphan*/  UENUM ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  usb_configured () ; 

int8_t usb_extra_send(uint8_t report_id, uint16_t data) {
    uint8_t intr_state, timeout;

    if (!usb_configured()) return -1;
    intr_state = SREG;
    cli();
    UENUM   = EXTRA_ENDPOINT;
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
        UENUM = EXTRA_ENDPOINT;
    }

    UEDATX = report_id;
    UEDATX = data & 0xFF;
    UEDATX = (data >> 8) & 0xFF;

    UEINTX = 0x3A;
    SREG   = intr_state;
    return 0;
}