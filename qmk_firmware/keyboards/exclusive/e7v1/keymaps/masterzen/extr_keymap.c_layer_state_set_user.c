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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ BASE ; 
#define  _ADJUST 128 
 int biton32 (scalar_t__) ; 
 int edit ; 
 int /*<<< orphan*/  hue ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  rgblight_get_hue () ; 
 int /*<<< orphan*/  rgblight_get_mode () ; 
 int /*<<< orphan*/  rgblight_get_sat () ; 
 int /*<<< orphan*/  rgblight_get_val () ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 
 int /*<<< orphan*/  sat ; 
 int /*<<< orphan*/  val ; 

uint32_t layer_state_set_user(uint32_t state)
{
  if (state == BASE && edit == true)
  {
    hue = rgblight_get_hue();
    sat = rgblight_get_sat();
    val = rgblight_get_val();
    edit = false;
  }

  switch (biton32(state))
  {
  case _ADJUST:
    mode = rgblight_get_mode();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(0xD3, 0x7F, 0xED);
    edit = true;
    break;
  default:
    rgblight_mode(mode);
    rgblight_sethsv(hue, sat, val);
    break;
  }
  return state;
}