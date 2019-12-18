#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BUFF_SIZE ; 
#define  KC_BSPC 135 
#define  KC_DOWN 134 
#define  KC_ENTER 133 
#define  KC_ESC 132 
#define  KC_KP_ENTER 131 
#define  KC_LEFT 130 
 int /*<<< orphan*/  KC_LSHIFT ; 
#define  KC_RIGHT 129 
 int /*<<< orphan*/  KC_RSHIFT ; 
#define  KC_UP 128 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int QK_LAYER_TAP ; 
 int QK_LAYER_TAP_MAX ; 
 int QK_MOD_TAP ; 
 int QK_MOD_TAP_MAX ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/ * SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TERMINAL_BELL () ; 
 int TERM_OFF ; 
 int TERM_ON ; 
 int /*<<< orphan*/  X_BSPACE ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  check_pos () ; 
 int /*<<< orphan*/ * cmd_buffer ; 
 size_t current_cmd_buffer_pos ; 
 int /*<<< orphan*/  disable_terminal () ; 
 int /*<<< orphan*/  enable_terminal () ; 
 int get_mods () ; 
 char* keycode_to_ascii_lut ; 
 int /*<<< orphan*/  process_terminal_command () ; 
 int /*<<< orphan*/  push_to_cmd_buffer () ; 
 int /*<<< orphan*/  send_string (int /*<<< orphan*/ *) ; 
 char* shifted_keycode_to_ascii_lut ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncat (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ terminal_enabled ; 

bool process_terminal(uint16_t keycode, keyrecord_t *record) {
    if (keycode == TERM_ON && record->event.pressed) {
        enable_terminal();
        return false;
    }

    if (terminal_enabled && record->event.pressed) {
        if (keycode == TERM_OFF && record->event.pressed) {
            disable_terminal();
            return false;
        }

        if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
            keycode = keycode & 0xFF;
        }

        if (keycode < 256) {
            uint8_t str_len;
            char    char_to_add;
            switch (keycode) {
                case KC_ENTER:
                case KC_KP_ENTER:
                    push_to_cmd_buffer();
                    current_cmd_buffer_pos = 0;
                    process_terminal_command();
                    return false;
                    break;
                case KC_ESC:
                    SEND_STRING("\n");
                    enable_terminal();
                    return false;
                    break;
                case KC_BSPC:
                    str_len = strlen(buffer);
                    if (str_len > 0) {
                        buffer[str_len - 1] = 0;
                        return true;
                    } else {
                        TERMINAL_BELL();
                        return false;
                    }
                    break;
                case KC_LEFT:
                    return false;
                    break;
                case KC_RIGHT:
                    return false;
                    break;
                case KC_UP:                                             // 0 = recent
                    check_pos();                                        // check our current buffer position is valid
                    if (current_cmd_buffer_pos <= CMD_BUFF_SIZE - 1) {  // once we get to the top, dont do anything
                        str_len = strlen(buffer);
                        for (int i = 0; i < str_len; ++i) {
                            send_string(SS_TAP(X_BSPACE));  // clear w/e is on the line already
                            // process_terminal(KC_BSPC,record);
                        }
                        strncpy(buffer, cmd_buffer[current_cmd_buffer_pos], 80);

                        send_string(buffer);
                        ++current_cmd_buffer_pos;  // get ready to access the above cmd if up/down is pressed again
                    }
                    return false;
                    break;
                case KC_DOWN:
                    check_pos();
                    if (current_cmd_buffer_pos >= 0) {  // once we get to the bottom, dont do anything
                        str_len = strlen(buffer);
                        for (int i = 0; i < str_len; ++i) {
                            send_string(SS_TAP(X_BSPACE));  // clear w/e is on the line already
                            // process_terminal(KC_BSPC,record);
                        }
                        strncpy(buffer, cmd_buffer[current_cmd_buffer_pos], 79);

                        send_string(buffer);
                        --current_cmd_buffer_pos;  // get ready to access the above cmd if down/up is pressed again
                    }
                    return false;
                    break;
                default:
                    if (keycode <= 58) {
                        char_to_add = 0;
                        if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
                            char_to_add = shifted_keycode_to_ascii_lut[keycode];
                        } else if (get_mods() == 0) {
                            char_to_add = keycode_to_ascii_lut[keycode];
                        }
                        if (char_to_add != 0) {
                            strncat(buffer, &char_to_add, 1);
                        }
                    }
                    break;
            }
        }
    }
    return true;
}