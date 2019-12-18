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
 unsigned long COL ; 
 unsigned long DVO ; 
#define  LAY_COL 134 
#define  LAY_DVO 133 
#define  LAY_QWE 132 
#define  LAY_WOR 131 
#define  OS_LIN 130 
#define  OS_MAC 129 
#define  OS_WIN 128 
 unsigned long QWE ; 
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  UC_OSX ; 
 int /*<<< orphan*/  UC_WINC ; 
 unsigned long WOR ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* layout switcher */
    case LAY_QWE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<QWE);
      }
      return false;
      break;
    case LAY_COL:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<COL);
      }
      return false;
      break;
    case LAY_WOR:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<WOR);
      }
      return false;
      break;
    case LAY_DVO:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<DVO);
      }
      return false;
      break;

    /* os switcher */
    case OS_LIN:
      set_unicode_input_mode(UC_LNX);
      return false;
      break;
    case OS_WIN:
      set_unicode_input_mode(UC_WINC);
      return false;
      break;
    case OS_MAC:
      set_unicode_input_mode(UC_OSX);
      return false;
      break;

  }
  return true;
}