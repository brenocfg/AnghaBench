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
 int /*<<< orphan*/  matrix_break (int) ; 
 int /*<<< orphan*/  matrix_make (int) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int move_e0code (int) ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 
 int xt_host_recv () ; 

uint8_t matrix_scan(void)
{
    static enum {
        XT_STATE_INIT,
        XT_STATE_E0,
        // Pause: E1 1D 45, E1 9D C5
        XT_STATE_E1,
        XT_STATE_E1_1D,
        XT_STATE_E1_9D,
    } state = XT_STATE_INIT;

    uint8_t code = xt_host_recv();
    if (!code) return 0;
    xprintf("%02X ", code);
    switch (state) {
        case XT_STATE_INIT:
            switch (code) {
                case 0xE0:
                    state = XT_STATE_E0;
                    break;
                case 0xE1:
                    state = XT_STATE_E1;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(code);
                    else
                        matrix_break(code & 0x7F);
                    break;
            }
            break;
        case XT_STATE_E0:
            switch (code) {
                case 0x2A:
                case 0xAA:
                case 0x36:
                case 0xB6:
                    //ignore fake shift
                    state = XT_STATE_INIT;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(move_e0code(code));
                    else
                        matrix_break(move_e0code(code & 0x7F));
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1:
            switch (code) {
                case 0x1D:
                    state = XT_STATE_E1_1D;
                    break;
                case 0x9D:
                    state = XT_STATE_E1_9D;
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1_1D:
            switch (code) {
                case 0x45:
                    matrix_make(0x55);
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1_9D:
            switch (code) {
                case 0x45:
                    matrix_break(0x55);
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        default:
            state = XT_STATE_INIT;
    }
    matrix_scan_quantum();
    return 1;
}