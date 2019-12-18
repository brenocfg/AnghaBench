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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RALT ; 
 int /*<<< orphan*/ * ascii_to_altgr_lut ; 
 int /*<<< orphan*/ * ascii_to_keycode_lut ; 
 int /*<<< orphan*/ * ascii_to_shift_lut ; 
 void* pgm_read_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (size_t) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void send_char(char ascii_code) {
    uint8_t keycode    = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
    bool    is_shifted = pgm_read_byte(&ascii_to_shift_lut[(uint8_t)ascii_code]);
    bool    is_altgred = pgm_read_byte(&ascii_to_altgr_lut[(uint8_t)ascii_code]);

    if (is_shifted) {
        register_code(KC_LSFT);
    }
    if (is_altgred) {
        register_code(KC_RALT);
    }
    tap_code(keycode);
    if (is_altgred) {
        unregister_code(KC_RALT);
    }
    if (is_shifted) {
        unregister_code(KC_LSFT);
    }
}