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
#define  ADJUST 133 
 int /*<<< orphan*/  AMPR ; 
 int /*<<< orphan*/  ASTR ; 
 int /*<<< orphan*/  AT ; 
 int BSLASH ; 
 int /*<<< orphan*/  BSLS ; 
 int BSPACE ; 
 int /*<<< orphan*/  CASE_US (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIRC ; 
 int /*<<< orphan*/  CSTM_0 ; 
 int /*<<< orphan*/  CSTM_1 ; 
 int /*<<< orphan*/  CSTM_2 ; 
 int /*<<< orphan*/  CSTM_3 ; 
 int /*<<< orphan*/  CSTM_4 ; 
 int /*<<< orphan*/  CSTM_5 ; 
 int /*<<< orphan*/  CSTM_6 ; 
 int /*<<< orphan*/  CSTM_7 ; 
 int /*<<< orphan*/  CSTM_8 ; 
 int /*<<< orphan*/  CSTM_9 ; 
 int /*<<< orphan*/  DEL ; 
 int DELETE ; 
 int /*<<< orphan*/  DLR ; 
 int /*<<< orphan*/  EQL ; 
 int EQUAL ; 
 int /*<<< orphan*/  EXLM ; 
 int GRAVE ; 
 int /*<<< orphan*/  GRV ; 
 int /*<<< orphan*/  HASH ; 
 int INT1 ; 
 int INT3 ; 
#define  JP 132 
 int /*<<< orphan*/  JP_LAYOUT ; 
 int /*<<< orphan*/  KEY (int) ; 
 int /*<<< orphan*/  KEY_SHIFT (int) ; 
 int /*<<< orphan*/  KEY_UPSHIFT (int) ; 
 int /*<<< orphan*/  LAYOUT_STATUS ; 
 int LBRACKET ; 
 int /*<<< orphan*/  LBRC ; 
 int /*<<< orphan*/  LCBR ; 
#define  LOWER 131 
 int /*<<< orphan*/  LPRN ; 
 int /*<<< orphan*/  MINS ; 
 int MINUS ; 
 int NONUS_HASH ; 
 int /*<<< orphan*/  PERC ; 
 int /*<<< orphan*/  PIPE ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  QUOT ; 
 int QUOTE ; 
#define  RAISE 130 
 int RBRACKET ; 
 int /*<<< orphan*/  RBRC ; 
 int /*<<< orphan*/  RCBR ; 
 int /*<<< orphan*/  RPRN ; 
 int /*<<< orphan*/  SCLN ; 
 int SCOLON ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
#define  SHIFT 129 
 int /*<<< orphan*/  SHIFT_DU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHIFT_PRESSED ; 
 int /*<<< orphan*/  SS_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TILD ; 
 int /*<<< orphan*/  UNDS ; 
#define  US 128 
 int /*<<< orphan*/  US_LAYOUT ; 
 int /*<<< orphan*/  X_LSHIFT ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        CASE_US(CSTM_0, KEY(0), SHIFT_DU(KEY_SHIFT(9), KEY(0)));
        CASE_US(CSTM_1, KEY(1), KEY(1));
        CASE_US(CSTM_2, KEY(2), SHIFT_DU(KEY_UPSHIFT(LBRACKET), KEY(2)));
        CASE_US(CSTM_3, KEY(3), KEY(3));
        CASE_US(CSTM_4, KEY(4), KEY(4));
        CASE_US(CSTM_5, KEY(5), KEY(5));
        CASE_US(CSTM_6, KEY(6), SHIFT_DU(KEY_UPSHIFT(EQUAL), KEY(6)));
        CASE_US(CSTM_7, KEY(7), SHIFT_DU(KEY_SHIFT(6), KEY(7)));
        CASE_US(CSTM_8, KEY(8), SHIFT_DU(KEY_SHIFT(QUOTE), KEY(8)));
        CASE_US(CSTM_9, KEY(9), SHIFT_DU(KEY_SHIFT(8), KEY(9)));
        CASE_US(DEL, KEY(DELETE), KEY_UPSHIFT(BSPACE));
        CASE_US(TILD, KEY_SHIFT(GRAVE), KEY_SHIFT(EQUAL));
        CASE_US(EXLM, KEY_SHIFT(1), KEY_SHIFT(1));
        CASE_US(AT, KEY_SHIFT(2), KEY(LBRACKET));
        CASE_US(HASH, KEY_SHIFT(3), KEY_SHIFT(3));
        CASE_US(DLR, KEY_SHIFT(4), KEY_SHIFT(4));
        CASE_US(PERC, KEY_SHIFT(5), KEY_SHIFT(5));
        CASE_US(CIRC, KEY_SHIFT(6), KEY(EQUAL));
        CASE_US(AMPR, KEY_SHIFT(7), KEY_SHIFT(6));
        CASE_US(ASTR, KEY_SHIFT(8), KEY_SHIFT(QUOTE));
        CASE_US(LPRN, KEY_SHIFT(9), KEY_SHIFT(8));
        CASE_US(RPRN, KEY_SHIFT(0), KEY_SHIFT(9));
        CASE_US(LBRC, KEY(LBRACKET), SHIFT_DU(KEY_SHIFT(RBRACKET), KEY(RBRACKET)));
        CASE_US(RBRC, KEY(RBRACKET), SHIFT_DU(KEY_SHIFT(NONUS_HASH), KEY(NONUS_HASH)));
        CASE_US(LCBR, KEY_SHIFT(LBRACKET), KEY_SHIFT(RBRACKET));
        CASE_US(RCBR, KEY_SHIFT(RBRACKET), KEY_SHIFT(NONUS_HASH));
        CASE_US(GRV, KEY(GRAVE), SHIFT_DU(KEY_SHIFT(EQUAL), KEY_SHIFT(LBRACKET)));
        CASE_US(BSLS, KEY(BSLASH), SHIFT_DU(KEY_SHIFT(INT3), KEY(INT3)));
        CASE_US(PIPE, KEY_SHIFT(BSLASH), KEY_SHIFT(INT3));
        CASE_US(MINS, KEY(MINUS), SHIFT_DU(KEY_SHIFT(INT1), KEY(MINUS)));
        CASE_US(UNDS, KEY_SHIFT(MINUS), KEY_SHIFT(INT1));
        CASE_US(EQL, KEY(EQUAL), SHIFT_DU(KEY_SHIFT(SCOLON), KEY_SHIFT(MINUS)));
        CASE_US(PLUS, KEY_SHIFT(EQUAL), KEY_SHIFT(SCOLON));
        CASE_US(SCLN, KEY(SCOLON), SHIFT_DU(KEY_UPSHIFT(QUOTE), KEY(SCOLON)));
        CASE_US(QUOT, KEY(QUOTE), SHIFT_DU(KEY_SHIFT(2), KEY_SHIFT(7)));
        case JP:
            if (record->event.pressed) {
                LAYOUT_STATUS = JP_LAYOUT;
            }
            return false;
            break;
        case US:
            if (record->event.pressed) {
                LAYOUT_STATUS = US_LAYOUT;
            }
            return false;
            break;
        case SHIFT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSHIFT));
                SHIFT_PRESSED = true;
            } else {
                SEND_STRING(SS_UP(X_LSHIFT));
                SHIFT_PRESSED = false;
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}