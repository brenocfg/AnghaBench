#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  pressed; } ;
typedef  TYPE_1__ keyevent_t ;

/* Variables and functions */
#define  CALC 152 
 char CALC_CHAR_ACS ; 
 char CALC_CHAR_ADD ; 
 char CALC_CHAR_ASN ; 
 char CALC_CHAR_ATN ; 
 char CALC_CHAR_BEG ; 
 char CALC_CHAR_COS ; 
 char CALC_CHAR_DEC ; 
 char CALC_CHAR_DIV ; 
 char CALC_CHAR_END ; 
 char CALC_CHAR_EUL ; 
 char CALC_CHAR_EXP ; 
 char CALC_CHAR_LGE ; 
 char CALC_CHAR_LOG ; 
 char CALC_CHAR_MUL ; 
 char CALC_CHAR_PI ; 
 char CALC_CHAR_SIN ; 
 char CALC_CHAR_SQT ; 
 char CALC_CHAR_SUB ; 
 char CALC_CHAR_TAN ; 
#define  ENDCALC 151 
#define  KC_0 150 
 int const KC_1 ; 
#define  KC_6 149 
#define  KC_8 148 
#define  KC_9 147 
#define  KC_BSPC 146 
#define  KC_C 145 
#define  KC_DOT 144 
#define  KC_E 143 
#define  KC_EQUAL 142 
 int const KC_KP_0 ; 
 int const KC_KP_1 ; 
 int const KC_KP_9 ; 
#define  KC_KP_ASTERISK 141 
#define  KC_KP_DOT 140 
#define  KC_KP_MINUS 139 
#define  KC_KP_PLUS 138 
#define  KC_KP_SLASH 137 
#define  KC_L 136 
#define  KC_LSFT 135 
#define  KC_MINUS 134 
#define  KC_P 133 
#define  KC_Q 132 
#define  KC_RSFT 131 
#define  KC_S 130 
#define  KC_SLASH 129 
#define  KC_T 128 
 int MODS_SHIFT_MASK ; 
 int get_mods () ; 

__attribute__((used)) static int process_input(const uint16_t keycode, const uint8_t mods, const keyevent_t event)
{
  /* handle even when no key was pressed */
  if(!event.pressed)
  {
    switch(keycode)
    {
      /* QMK should handle those */
      case KC_RSFT:
      case KC_LSFT:
        return 0;
        break;
    }
    /* ??? ignore */
    return -1;
  }

  /* when shift key is pressed handle characters differently */
  char characterPressed;
  if((get_mods() & MODS_SHIFT_MASK))
  {
    switch(keycode)
    {
      case KC_9:
        characterPressed = CALC_CHAR_BEG;
        break;
      case KC_0:
        characterPressed = CALC_CHAR_END;
        break;
      case KC_EQUAL:
        characterPressed = CALC_CHAR_ADD;
        break;
      case KC_KP_PLUS:
        characterPressed = CALC_CHAR_ADD;
        break;
      case KC_6:
        characterPressed = CALC_CHAR_EXP;
        break;
      case KC_8:
        characterPressed = CALC_CHAR_MUL;
        break;
      case KC_KP_ASTERISK:
        characterPressed = CALC_CHAR_MUL;
        break;
      case KC_S:
        characterPressed = CALC_CHAR_ASN;
        break;
      case KC_C:
        characterPressed = CALC_CHAR_ACS;
        break;
      case KC_T:
        characterPressed = CALC_CHAR_ATN;
        break;
      case KC_L:
        characterPressed = CALC_CHAR_LOG;
        break;
      default:
        return -1;
        break;
    }
    return characterPressed;
  }

  /* normal key handling:  shift not pressed */

  /* digits */
  if (keycode == KC_KP_0 || keycode == KC_0) {
    return '0';
  } else if (keycode >= KC_KP_1 && keycode <= KC_KP_9) {
    return keycode - KC_KP_1 +1 + '0';
  } else if (keycode >= KC_1 && keycode <= KC_9) {
    return keycode - KC_1 +1 + '0';
  }

  /* other tokens */
  switch (keycode) {
    case KC_MINUS:
    case KC_KP_MINUS:
      return characterPressed = CALC_CHAR_SUB;
    case KC_SLASH:
    case KC_KP_SLASH:
      return characterPressed = CALC_CHAR_DIV;
    case KC_S:
      return characterPressed = CALC_CHAR_SIN;
    case KC_C:
      return characterPressed = CALC_CHAR_COS;
    case KC_T:
      return characterPressed = CALC_CHAR_TAN;
    case KC_Q:
      return characterPressed = CALC_CHAR_SQT;
    case KC_L:
      return characterPressed = CALC_CHAR_LGE;
    case KC_DOT:
    case KC_KP_DOT:
      return characterPressed = CALC_CHAR_DEC;
    case KC_P:
      return characterPressed = CALC_CHAR_PI;
    case KC_E:
      return characterPressed = CALC_CHAR_EUL;
    case KC_BSPC:
      return -2;
    case KC_RSFT:
      return 0;
    case KC_LSFT:
      return 0;
    case CALC:
      return -3;
    case ENDCALC:
      return -4;
    default:
      return -1;
  }
}