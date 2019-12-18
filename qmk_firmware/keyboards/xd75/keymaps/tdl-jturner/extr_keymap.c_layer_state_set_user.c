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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _LYFK 135 
#define  _LYLT 134 
#define  _LYMD 133 
#define  _LYMED 132 
#define  _LYMOS 131 
#define  _LYNAV 130 
#define  _LYNUM 129 
#define  _LYSYS 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYFK () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYLT () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYMD () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYMED () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYMOS () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYNAV () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYNUM () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_LYSYS () ; 
 int /*<<< orphan*/  rgblight_setrgb_user_base () ; 

uint32_t layer_state_set_user(uint32_t state) {
  switch(biton32(state)) {
    case _LYFK:
      rgblight_setrgb_user_LYFK();
      break;
    case _LYMED:
      rgblight_setrgb_user_LYMED();
      break;
    case _LYNUM:
      rgblight_setrgb_user_LYNUM();
      break;
    case _LYNAV:
      rgblight_setrgb_user_LYNAV();
      break;
    case _LYMOS:
      rgblight_setrgb_user_LYMOS();
      break;
    case _LYSYS:
      rgblight_setrgb_user_LYSYS();
      break;
    case _LYLT:
      rgblight_setrgb_user_LYLT();
      break;
    case _LYMD:
      rgblight_setrgb_user_LYMD();
      break;
    default:
      rgblight_setrgb_user_base();
      break;
  }
  return state;
}