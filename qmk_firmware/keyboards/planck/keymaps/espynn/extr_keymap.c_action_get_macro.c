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
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int ENT ; 
 int J ; 
 int /*<<< orphan*/  KC_2 ; 
 int /*<<< orphan*/  KC_A ; 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_DOT ; 
 int /*<<< orphan*/  KC_F ; 
 int /*<<< orphan*/  KC_G ; 
 int /*<<< orphan*/  KC_I ; 
 int /*<<< orphan*/  KC_L ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_M ; 
 int /*<<< orphan*/  KC_O ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  KC_X ; 
 int /*<<< orphan*/  const* MACRODOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int MINS ; 
 int /*<<< orphan*/  T (int) ; 
 int /*<<< orphan*/  TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP (int /*<<< orphan*/ ) ; 
 int W ; 
#define  _BL 139 
#define  _COPY 138 
#define  _CUS0 137 
#define  _CUS1 136 
#define  _CUS2 135 
#define  _CUS3 134 
#define  _CUS4 133 
#define  _CUS5 132 
 int /*<<< orphan*/  _CUSTOM ; 
#define  _CUT 131 
#define  _LOWER 130 
#define  _PASTE 129 
#define  _RAISE 128 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  layer_off (int const) ; 
 int /*<<< orphan*/  layer_on (int const) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int const,int const,int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case _RAISE: // Raised layer.
	if (record->event.pressed) {
	    layer_on(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_RAISE);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _LOWER: // Lowered layer.
	if (record->event.pressed) {
	    layer_on(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	} else {
	    layer_off(_LOWER);
	    update_tri_layer(_LOWER, _RAISE, _CUSTOM);
	}
	break;
    case _BL: // Backlight
	if (record->event.pressed) {
	    register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
	    backlight_step();
#endif
	} else {
	    unregister_code(KC_RSFT);
	}
	break;
    case _CUS0: // enter your mobile# here
	    return MACRODOWN(T(9), T(9), T(9), T(MINS),T(9), T(9), T(9), T(MINS),T(9), T(9), T(9), T(9),END);
    case _CUS1: // signature line for email
	    return MACRODOWN(T(ENT), T(ENT), T(MINS), T(J), T(W), END);
    case _CUS2: // Custom macro 2
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_L), UP(KC_LSFT), END );
    case _CUS3: // custom macro 3
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_F), UP(KC_LSFT), END );
    case _CUS4: // custom macro 4
	    return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_I), UP(KC_LSFT), END );
    case _CUS5: // Enter your email here
	    return MACRODOWN( TYPE(KC_F),
        DOWN(KC_LSFT), TYPE(KC_2), UP(KC_LSFT),
        TYPE(KC_G), TYPE(KC_M), TYPE(KC_A), TYPE(KC_I), TYPE(KC_L), TYPE(KC_DOT), TYPE(KC_C), TYPE(KC_O), TYPE(KC_M), END );
    case _CUT: //cut macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_X), UP(KC_LCTL), END );
    case _COPY: // copy macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_C), UP(KC_LCTL), END );
    case _PASTE: // paste macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_V), UP(KC_LCTL), END );
    };
    return MACRO_NONE;
}