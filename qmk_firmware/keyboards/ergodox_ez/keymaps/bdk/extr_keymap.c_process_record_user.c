#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  KC_ENTER 131 
 int KC_ESC ; 
 int KC_LCTL ; 
#define  KC_LSFT 130 
#define  KC_RSFT 129 
#define  KC_TAB 128 
 int /*<<< orphan*/  MOD_BIT (int) ; 
 int /*<<< orphan*/  SYMNUM ; 
 int handle_lt (int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int handle_mt (int,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ key_down (int) ; 
 int /*<<< orphan*/  press_counter ; 
 int /*<<< orphan*/  unregister_code (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        press_counter++;
        // The symbol layer allows sequences repeat the same "physical" key.
        // For example "0)", which is like pressing the "0" key twice in a
        // row.  It's very easy to make a sequence of these where the ")"
        // press comes before the "0" release.  If that happens, force a
        // release of the "0" key, otherwise nothing will happen.
        uint8_t shortcode = keycode & 0xFF;
        if(key_down(shortcode)) {
            unregister_code(shortcode);
        }
    }

    switch(keycode) {
        case KC_ENTER:
            return handle_lt(keycode, record, SYMNUM, 0);

        case KC_TAB:
            return handle_mt(keycode, record, MOD_BIT(KC_LCTL), 1);

        case KC_LSFT:
        case KC_RSFT:
            return handle_mt(KC_ESC, record, MOD_BIT(keycode), 2);
    }
    return true;
}