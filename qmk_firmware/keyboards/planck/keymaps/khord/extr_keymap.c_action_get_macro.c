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
#define  MACRO_BREATH_DEFAULT 131 
#define  MACRO_BREATH_SPEED_DEC 130 
#define  MACRO_BREATH_SPEED_INC 129 
#define  MACRO_BREATH_TOGGLE 128 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  breathing_period_dec () ; 
 int /*<<< orphan*/  breathing_period_default () ; 
 int /*<<< orphan*/  breathing_period_inc () ; 
 int /*<<< orphan*/  breathing_toggle () ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case MACRO_BREATH_TOGGLE:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_BREATHING
          breathing_toggle();
        #endif
      }
      break;
    case MACRO_BREATH_SPEED_INC:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_BREATHING
          breathing_period_inc();
        #endif
      }
      break;
    case MACRO_BREATH_SPEED_DEC:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_BREATHING
          breathing_period_dec();
        #endif
      }
      break;
    case MACRO_BREATH_DEFAULT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_BREATHING
          breathing_period_default();
        #endif
      }
      break;
  }
  return MACRO_NONE;
}