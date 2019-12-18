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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  RGB_000 131 
#define  RGB_OAZ 130 
#define  RGB_VAZ 129 
#define  RGB_WAN 128 
 int /*<<< orphan*/  rgblight_disable () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case RGB_VAZ:
        rgblight_enable();
        rgblight_setrgb(0, 204, 33);
        break;
      case RGB_OAZ:
        rgblight_enable();
        rgblight_setrgb(229, 65, 0);
        break;
      case RGB_WAN:
        rgblight_enable();
        rgblight_setrgb(255, 255, 255);
        break;
      case RGB_000:
        rgblight_disable();
        break;
    }
  }
  return true;
}