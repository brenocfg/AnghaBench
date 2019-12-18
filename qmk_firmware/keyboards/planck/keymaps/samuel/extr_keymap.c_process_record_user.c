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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_0 ; 
 int /*<<< orphan*/  KC_9 ; 
 int /*<<< orphan*/  KC_BSLASH ; 
 int /*<<< orphan*/  KC_C ; 
#define  KC_COM 156 
 int /*<<< orphan*/  KC_DELETE ; 
#define  KC_DIR 155 
 int /*<<< orphan*/  KC_DOWN ; 
#define  KC_DVORAK 154 
#define  KC_EMAIL 153 
 int /*<<< orphan*/  KC_EQUAL ; 
#define  KC_EZALT 152 
#define  KC_EZCOPY 151 
#define  KC_EZCTRL 150 
#define  KC_EZCUT 149 
#define  KC_EZDOWN 148 
#define  KC_EZGUI 147 
#define  KC_EZLEFT 146 
#define  KC_EZPSTE 145 
#define  KC_EZRGHT 144 
#define  KC_EZSHFT 143 
#define  KC_EZUNDO 142 
#define  KC_EZUP 141 
 int /*<<< orphan*/  KC_GRAVE ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LBRACKET ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_MINUS ; 
#define  KC_NAME 140 
#define  KC_QWERTY 139 
 int /*<<< orphan*/  KC_RALT ; 
 int /*<<< orphan*/  KC_RBRACKET ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RGHT ; 
 int /*<<< orphan*/  KC_RGUI ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_SLASH ; 
#define  KC_T_LALT 138 
#define  KC_T_LCTL 137 
#define  KC_T_LGUI 136 
#define  KC_T_LRSE 135 
#define  KC_T_LSFT 134 
#define  KC_T_RALT 133 
#define  KC_T_RCTL 132 
#define  KC_T_RGUI 131 
#define  KC_T_RRSE 130 
#define  KC_T_RSFT 129 
 int /*<<< orphan*/  KC_UP ; 
#define  KC_USER 128 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  KC_X ; 
 int /*<<< orphan*/  KC_Z ; 
 int /*<<< orphan*/  MOD_LALT ; 
 int /*<<< orphan*/  MOD_LCTL ; 
 int /*<<< orphan*/  MOD_LGUI ; 
 int /*<<< orphan*/  MOD_LSFT ; 
 int /*<<< orphan*/  ONESHOT_PRESSED ; 
 int /*<<< orphan*/  ONESHOT_START ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAPPING_TERM ; 
 int /*<<< orphan*/  _COMMAND ; 
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RISE ; 
 int /*<<< orphan*/  clear_oneshot_layer_state (int /*<<< orphan*/ ) ; 
 int last_mod ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_lift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_press (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_string (char*) ; 
 int /*<<< orphan*/  set_oneshot_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_oneshot_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_timer ; 
 int /*<<< orphan*/  timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

case KC_DVORAK:
if (record->event.pressed) {
    set_single_persistent_default_layer(_DVORAK);
}
return true;
break;

case KC_QWERTY:
if (record->event.pressed) {
    set_single_persistent_default_layer(_QWERTY);
}
return true;
break;

case KC_T_LALT:
if (record->event.pressed) {
    mod_press(S(KC_9), KC_LALT, 0);
} else {
    mod_lift(S(KC_9), KC_LALT, 0);
}
return false;
break;
case KC_T_RALT:
if (record->event.pressed) {
    mod_press(S(KC_0), KC_RALT, 1);
} else {
    mod_lift(S(KC_0), KC_RALT, 1);
}
return false;
break;

case KC_T_LGUI:
if (record->event.pressed) {
    mod_press(KC_GRAVE, KC_LGUI, 2);
} else {
    mod_lift(KC_GRAVE, KC_LGUI, 2);
}
return false;
break;
case KC_T_RGUI:
if (record->event.pressed) {
    mod_press(KC_BSLASH, KC_RGUI, 3);
} else {
    mod_lift(KC_BSLASH, KC_RGUI, 3);
}
return false;
break;

case KC_T_LCTL:
if (record->event.pressed) {
    mod_press(KC_LBRACKET, KC_LCTL, 4);
} else {
    mod_lift(KC_LBRACKET, KC_LCTL, 4);
}
return false;
break;
case KC_T_RCTL:
if (record->event.pressed) {
    mod_press(KC_RBRACKET, KC_RCTL, 5);
} else {
    mod_lift(KC_RBRACKET, KC_RCTL, 5);
}
return false;
break;

case KC_T_LSFT:
if (record->event.pressed) {
    mod_press(KC_EQUAL, KC_LSFT, 6);
} else {
    mod_lift(KC_EQUAL, KC_LSFT, 6);
}
return false;
break;
case KC_T_RSFT:
if (record->event.pressed) {
    mod_press(KC_MINUS, KC_RSFT, 7);
} else {
    mod_lift(KC_MINUS, KC_RSFT, 7);
}
return false;
break;

case KC_T_LRSE:
if (record->event.pressed) {
    tap_timer = timer_read();
    last_mod = 8;
    layer_on(_RISE);
} else {
    layer_off(_RISE);
    if (last_mod == 8 && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(KC_DELETE);
        last_mod = 10;
    }
}
return false;
break;
case KC_T_RRSE:
if (record->event.pressed) {
    tap_timer = timer_read();
    last_mod = 9;
    layer_on(_RISE);
} else {
    layer_off(_RISE);
    if (last_mod == 9 && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(KC_SLASH);
        last_mod = 10;
    }
}
return false;
break;

case KC_EZSHFT:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LSFT);
    last_mod = 10;
}
return false;
break;
case KC_EZCTRL:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZALT:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LALT);
    last_mod = 10;
}
return false;
break;
case KC_EZGUI:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LGUI);
    last_mod = 10;
}
return false;
break;

case KC_EZRGHT:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_RGHT));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZLEFT:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_LEFT));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZDOWN:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_DOWN));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZUP:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_UP));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;

case KC_EZUNDO:
if (record->event.pressed) {
    tap_code16(C(KC_Z));
    last_mod = 10;
}
return false;
break;
case KC_EZCOPY:
if (record->event.pressed) {
    tap_code16(C(KC_C));
    last_mod = 10;
}
return false;
break;
case KC_EZCUT:
if (record->event.pressed) {
    tap_code16(C(KC_X));
    last_mod = 10;
}
return false;
break;
case KC_EZPSTE:
if (record->event.pressed) {
    tap_code16(C(KC_V));
    last_mod = 10;
}
return false;
break;

case KC_COM:
if (record->event.pressed) {
    layer_on(_COMMAND);
    set_oneshot_layer(_COMMAND, ONESHOT_START);
    last_mod = 10;
} else {
    clear_oneshot_layer_state (ONESHOT_PRESSED);
}
return false;
break;

case KC_USER:
if (record->event.pressed) {
    send_string("mhostley");
    last_mod = 10;
}
return true;
break;
case KC_EMAIL:
if (record->event.pressed) {
    send_string("mhostley@gmail.com");
    last_mod = 10;
}
return true;
break;
case KC_NAME:
if (record->event.pressed) {
    send_string("Samuel Jahnke");
    last_mod = 10;
}
return true;
break;
case KC_DIR:
if (record->event.pressed) {
    send_string("home/mhostley/");
    last_mod = 10;
}
return true;
break;

}
last_mod = 10;
return true;
}