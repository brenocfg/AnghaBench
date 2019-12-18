#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LCMD ; 
 int /*<<< orphan*/  KC_LCTL ; 
#define  ampr 148 
#define  astr 147 
#define  at 146 
#define  bsls 145 
#define  circ 144 
#define  cmd 143 
 int cmd_keys_down ; 
#define  dlr 142 
#define  eql 141 
#define  exlm 140 
#define  grv 139 
#define  hash 138 
#define  lbrc 137 
#define  lcbr 136 
#define  lprn 135 
#define  perc 134 
#define  pipe 133 
#define  plus 132 
#define  rbrc 131 
#define  rcbr 130 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
#define  rprn 129 
 int send_string_if_keydown (TYPE_2__*,char*) ; 
#define  tild 128 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Override the defualt auto shifted symbols to use SEND_STRING See
        // https://github.com/qmk/qmk_firmware/issues/4072
        case ampr:
            return send_string_if_keydown(record, "&");
        case astr:
            return send_string_if_keydown(record, "*");
        case at:
            return send_string_if_keydown(record, "@");
        case bsls:
            return send_string_if_keydown(record, "\\");
        case circ:
            return send_string_if_keydown(record, "^");
        case dlr:
            return send_string_if_keydown(record, "$");
        case eql:
            return send_string_if_keydown(record, "=");
        case exlm:
            return send_string_if_keydown(record, "!");
        case grv:
            return send_string_if_keydown(record, "`");
        case hash:
            return send_string_if_keydown(record, "#");
        case lbrc:
            return send_string_if_keydown(record, "[");
        case lcbr:
            return send_string_if_keydown(record, "{");
        case lprn:
            return send_string_if_keydown(record, "(");
        case perc:
            return send_string_if_keydown(record, "%");
        case pipe:
            return send_string_if_keydown(record, "|");
        case plus:
            return send_string_if_keydown(record, "+");
        case rbrc:
            return send_string_if_keydown(record, "]");
        case rcbr:
            return send_string_if_keydown(record, "}");
        case rprn:
            return send_string_if_keydown(record, ")");
        case tild:
            return send_string_if_keydown(record, "~");

        // cmd + cmd -> cmd + ctl
        case cmd:
            if (record->event.pressed) {
                if (cmd_keys_down == 0) {
                    register_code(KC_LCMD);
                } else {
                    register_code(KC_LCTL);
                }
                cmd_keys_down++;
            } else {
                if (cmd_keys_down == 1) {
                    unregister_code(KC_LCMD);
                } else {
                    unregister_code(KC_LCTL);
                }
                cmd_keys_down--;
            }
            return true;
    }
    return true;
}