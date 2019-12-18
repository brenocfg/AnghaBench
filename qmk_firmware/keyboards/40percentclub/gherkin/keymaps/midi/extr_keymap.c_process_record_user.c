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
#define  AEOLIAN 134 
#define  DORIAN 133 
#define  IONIAN 132 
#define  LOCRIAN 131 
#define  LYDIAN 130 
#define  MIXOLYDIAN 129 
#define  PHRYGIAN 128 
 int /*<<< orphan*/  _AEOLIAN ; 
 int /*<<< orphan*/  _DORIAN ; 
 int /*<<< orphan*/  _IONIAN ; 
 int /*<<< orphan*/  _LOCRIAN ; 
 int /*<<< orphan*/  _LYDIAN ; 
 int /*<<< orphan*/  _MIXOLYDIAN ; 
 int /*<<< orphan*/  _PHRYGIAN ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case IONIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_IONIAN);
      }
      break;
    case DORIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DORIAN);
      }
      break;
    case PHRYGIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PHRYGIAN);
      }
      break;
    case LYDIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LYDIAN);
      }
      break;
    case MIXOLYDIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MIXOLYDIAN);
      }
      break;
    case AEOLIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_AEOLIAN);
      }
      break;
    case LOCRIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LOCRIAN);
      }
      break;
  }
  return true;
}