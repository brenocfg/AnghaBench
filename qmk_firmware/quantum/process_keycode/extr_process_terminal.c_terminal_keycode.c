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
typedef  size_t uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/ * arguments ; 
 int /*<<< orphan*/  itoa (size_t,char*,int) ; 
 int /*<<< orphan*/ *** keymaps ; 
 size_t pgm_read_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_string (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 size_t strtol (int /*<<< orphan*/ ,char**,int) ; 

void terminal_keycode(void) {
    if (strlen(arguments[1]) != 0 && strlen(arguments[2]) != 0 && strlen(arguments[3]) != 0) {
        char     keycode_dec[5];
        char     keycode_hex[5];
        uint16_t layer   = strtol(arguments[1], (char **)NULL, 10);
        uint16_t row     = strtol(arguments[2], (char **)NULL, 10);
        uint16_t col     = strtol(arguments[3], (char **)NULL, 10);
        uint16_t keycode = pgm_read_word(&keymaps[layer][row][col]);
        itoa(keycode, keycode_dec, 10);
        itoa(keycode, keycode_hex, 16);
        SEND_STRING("0x");
        send_string(keycode_hex);
        SEND_STRING(" (");
        send_string(keycode_dec);
        SEND_STRING(")\n");
    } else {
#ifdef TERMINAL_HELP
        SEND_STRING("usage: keycode <layer> <row> <col>\n");
#endif
    }
}