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

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (int) ; 
 int /*<<< orphan*/  matrix_break (int) ; 
 int /*<<< orphan*/  matrix_make (int) ; 
 int ps2_host_recv () ; 
 int ps2_host_send (int) ; 

uint8_t matrix_scan(void)
{

    // scan code reading states
    static enum {
        RESET,
        RESET_RESPONSE,
        KBD_ID0,
        KBD_ID1,
        CONFIG,
        READY,
        F0,
    } state = RESET;

    uint8_t code;
    if ((code = ps2_host_recv())) {
        debug("r"); debug_hex(code); debug(" ");
    }

    switch (state) {
        case RESET:
            debug("wFF ");
            if (ps2_host_send(0xFF) == 0xFA) {
                debug("[ack]\nRESET_RESPONSE: ");
                state = RESET_RESPONSE;
            }
            break;
        case RESET_RESPONSE:
            if (code == 0xAA) {
                debug("[ok]\nKBD_ID: ");
                state = KBD_ID0;
            } else if (code) {
                debug("err\nRESET: ");
                state = RESET;
            }
            break;
        // after reset receive keyboard ID(2 bytes)
        case KBD_ID0:
            if (code) {
                state = KBD_ID1;
            }
            break;
        case KBD_ID1:
            if (code) {
                debug("\nCONFIG: ");
                state = CONFIG;
            }
            break;
        case CONFIG:
            debug("wF8 ");
            if (ps2_host_send(0xF8) == 0xFA) {
                debug("[ack]\nREADY\n");
                state = READY;
            }
            break;
        case READY:
            switch (code) {
                case 0x00:
                    break;
                case 0xF0:
                    state = F0;
                    debug(" ");
                    break;
                default:    // normal key make
                    if (code < 0x88) {
                        matrix_make(code);
                    } else {
                        debug("unexpected scan code at READY: "); debug_hex(code); debug("\n");
                    }
                    state = READY;
                    debug("\n");
            }
            break;
        case F0:    // Break code
            switch (code) {
                case 0x00:
                    break;
                default:
                    if (code < 0x88) {
                        matrix_break(code);
                    } else {
                        debug("unexpected scan code at F0: "); debug_hex(code); debug("\n");
                    }
                    state = READY;
                    debug("\n");
            }
            break;
    }
    return 1;
}