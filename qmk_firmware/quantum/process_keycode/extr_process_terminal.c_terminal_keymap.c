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
 int MATRIX_COLS ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/ * arguments ; 
 int /*<<< orphan*/ *** keymaps ; 
 char* newline ; 
 size_t pgm_read_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_string (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 size_t strtol (int /*<<< orphan*/ ,char**,int) ; 

void terminal_keymap(void) {
    if (strlen(arguments[1]) != 0) {
        uint16_t layer = strtol(arguments[1], (char **)NULL, 10);
        for (int r = 0; r < MATRIX_ROWS; r++) {
            for (int c = 0; c < MATRIX_COLS; c++) {
                uint16_t keycode = pgm_read_word(&keymaps[layer][r][c]);
                char     keycode_s[8];
                sprintf(keycode_s, "0x%04x,", keycode);
                send_string(keycode_s);
            }
            send_string(newline);
        }
    } else {
#ifdef TERMINAL_HELP
        SEND_STRING("usage: keymap <layer>\n");
#endif
    }
}