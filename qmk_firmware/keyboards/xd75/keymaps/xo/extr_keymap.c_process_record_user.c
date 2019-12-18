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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_COLOR ; 
 scalar_t__ IS_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB_RED ; 
 int /*<<< orphan*/  backlight_level (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    backlight_level(4);
  } else {
    backlight_level(6);
  }

  if (IS_MOD(keycode)) {
    if (record->event.pressed) {
      rgblight_setrgb(RGB_RED);
    } else {
      rgblight_setrgb(BASE_COLOR);
    }
  }

  return true;
}