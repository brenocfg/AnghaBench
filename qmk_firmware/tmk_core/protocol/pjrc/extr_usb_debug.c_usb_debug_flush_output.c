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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX_ENDPOINT ; 
 int RWAL ; 
 int /*<<< orphan*/  SREG ; 
 scalar_t__ UEDATX ; 
 int UEINTX ; 
 int /*<<< orphan*/  UENUM ; 
 int /*<<< orphan*/  cli () ; 
 scalar_t__ debug_flush_timer ; 

void usb_debug_flush_output(void) {
    uint8_t intr_state;

    intr_state = SREG;
    cli();
    if (debug_flush_timer) {
        UENUM = DEBUG_TX_ENDPOINT;
        while ((UEINTX & (1 << RWAL))) {
            UEDATX = 0;
        }
        UEINTX            = 0x3A;
        debug_flush_timer = 0;
    }
    SREG = intr_state;
}