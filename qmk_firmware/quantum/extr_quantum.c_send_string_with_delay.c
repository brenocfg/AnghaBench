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
typedef  char uint8_t ;

/* Variables and functions */
 char SS_DOWN_CODE ; 
 char SS_TAP_CODE ; 
 char SS_UP_CODE ; 
 int /*<<< orphan*/  register_code (char) ; 
 int /*<<< orphan*/  send_char (char) ; 
 int /*<<< orphan*/  unregister_code (char) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void send_string_with_delay(const char *str, uint8_t interval) {
    while (1) {
        char ascii_code = *str;
        if (!ascii_code) break;
        if (ascii_code == SS_TAP_CODE) {
            // tap
            uint8_t keycode = *(++str);
            register_code(keycode);
            unregister_code(keycode);
        } else if (ascii_code == SS_DOWN_CODE) {
            // down
            uint8_t keycode = *(++str);
            register_code(keycode);
        } else if (ascii_code == SS_UP_CODE) {
            // up
            uint8_t keycode = *(++str);
            unregister_code(keycode);
        } else {
            send_char(ascii_code);
        }
        ++str;
        // interval
        {
            uint8_t ms = interval;
            while (ms--) wait_ms(1);
        }
    }
}