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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LED_CONFIG ; 
 int /*<<< orphan*/  DEBUG_LED_OFF ; 
 int /*<<< orphan*/  DEBUG_LED_ON ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 int /*<<< orphan*/  iwrap_mux_send (char*) ; 
 int /*<<< orphan*/  print_S (char*) ; 
 char* rcv_buf ; 
 int rcv_tail ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void iwrap_call(void) {
    char *p;

    iwrap_mux_send("SET BT PAIR");
    _delay_ms(500);

    p = rcv_buf + rcv_tail;
    while (!strncmp(p, "SET BT PAIR", 11)) {
        p += 7;
        strncpy(p, "CALL", 4);
        strncpy(p + 22, " 11 HID\n\0", 9);
        print_S(p);
        iwrap_mux_send(p);
        // TODO: skip to next line
        p += 57;

        DEBUG_LED_CONFIG;
        DEBUG_LED_ON;
        _delay_ms(500);
        DEBUG_LED_OFF;
        _delay_ms(500);
        DEBUG_LED_ON;
        _delay_ms(500);
        DEBUG_LED_OFF;
        _delay_ms(500);
        DEBUG_LED_ON;
        _delay_ms(500);
        DEBUG_LED_OFF;
        _delay_ms(500);
        DEBUG_LED_ON;
        _delay_ms(500);
        DEBUG_LED_OFF;
        _delay_ms(500);
        DEBUG_LED_ON;
        _delay_ms(500);
        DEBUG_LED_OFF;
        _delay_ms(500);
    }
    iwrap_check_connection();
}