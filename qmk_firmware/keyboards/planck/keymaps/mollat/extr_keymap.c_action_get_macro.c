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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  KC_0 ; 
 int /*<<< orphan*/  KC_1 ; 
 int /*<<< orphan*/  KC_2 ; 
 int /*<<< orphan*/  KC_3 ; 
 int /*<<< orphan*/  KC_4 ; 
 int /*<<< orphan*/  KC_5 ; 
 int /*<<< orphan*/  KC_6 ; 
 int /*<<< orphan*/  KC_7 ; 
 int /*<<< orphan*/  KC_8 ; 
 int /*<<< orphan*/  KC_B ; 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_ENT ; 
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_L ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_N ; 
 int /*<<< orphan*/  KC_P ; 
 int /*<<< orphan*/  KC_Q ; 
 int /*<<< orphan*/  KC_SCLN ; 
 int /*<<< orphan*/  KC_W ; 
 int /*<<< orphan*/  const* MACRODOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_0), END );
          break;
        case 1:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_1), END );
          break;
        case 2:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_2), END );
          break;
        case 3:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_3), END );
          break;
        case 4:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_4), END );
          break;
        case 5:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_5), END );
          break;
        case 6:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_6), END );
          break;
        case 7:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_7), END );
          break;
        case 8:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_8), END );
          break;
        case 9:
          // tmux last window
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_L), END );
          break;
          // tmux next window
        case 10:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_N), END );
          break;
          // tmux previous window
        case 11:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_P), END );
          break;
          // tmux new window
        case 12:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_C), END );
          break;
        case 13:
          // vi save document
          return MACRODOWN( TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN), UP(KC_LSFT), TYPE(KC_W), TYPE(KC_ENT), END );
          break;
        case 14:
          // vi quit
          return MACRODOWN( TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN), UP(KC_LSFT), TYPE(KC_Q), TYPE(KC_ENT), END );
          break;
          // tmux press ctrl-b
        case 15:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), END );
          break;
      }
    return MACRO_NONE;
}