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
 int COL (int) ; 
 int MATRIX_ROWS ; 
 size_t ROW (int) ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (int) ; 
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int /*<<< orphan*/  led_set (int /*<<< orphan*/ ) ; 
 int* matrix ; 
 scalar_t__ matrix_is_on (size_t,int) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  print (char*) ; 
 int serial_recv () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

uint8_t matrix_scan(void)
{
    uint8_t code;
    code = serial_recv();
    if (!code) return 0;

    debug_hex(code); debug(" ");

    switch (code) {
        case 0xFF:  // reset success: FF 04
            print("reset: ");
            _delay_ms(500);
            code = serial_recv();
            xprintf("%02X\n", code);
            if (code == 0x04) {
                // LED status
                led_set(host_keyboard_leds());
            }
            return 0;
        case 0xFE:  // layout: FE <layout>
            print("layout: ");
            _delay_ms(500);
            xprintf("%02X\n", serial_recv());
            return 0;
        case 0x7E:  // reset fail: 7E 01
            print("reset fail: ");
            _delay_ms(500);
            xprintf("%02X\n", serial_recv());
            return 0;
        case 0x7F:
            // all keys up
            for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
            return 0;
    }

    if (code&0x80) {
        // break code
        if (matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] &= ~(1<<COL(code));
        }
    } else {
        // make code
        if (!matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] |=  (1<<COL(code));
        }
    }

    matrix_scan_quantum();
    return code;
}