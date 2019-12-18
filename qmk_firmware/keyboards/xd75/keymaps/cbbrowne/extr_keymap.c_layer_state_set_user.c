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
#define  _ADJUST 132 
#define  _FUNCTION 131 
#define  _LOWER 130 
#define  _QWERTY 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv (int,int,int) ; 
 int /*<<< orphan*/  rgblight_sethsv_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_orange () ; 
 int /*<<< orphan*/  rgblight_sethsv_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_white () ; 

uint32_t layer_state_set_user(uint32_t state) {
  switch(biton32(state)) {
  case _QWERTY:
    rgblight_sethsv_white();
    break;
  case _LOWER:
    rgblight_sethsv_blue();
    break;
  case _RAISE:
    rgblight_sethsv_green();
    break;
  case _ADJUST:
    rgblight_sethsv_orange();
    break;
  case _FUNCTION:
    rgblight_sethsv_red();
    break;
  default:
    rgblight_sethsv(325,255,255);
    break;
  }
  return state;
}