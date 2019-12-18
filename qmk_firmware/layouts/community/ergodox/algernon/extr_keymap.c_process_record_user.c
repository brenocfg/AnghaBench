#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;
struct TYPE_6__ {scalar_t__ pressed; TYPE_1__ key; } ;
struct TYPE_7__ {TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ ADORE ; 
 scalar_t__ BASE ; 
 unsigned long HUN ; 
 int /*<<< orphan*/  KC_4 ; 
 scalar_t__ KC_A ; 
 scalar_t__ KC_D ; 
 scalar_t__ KC_E ; 
 int /*<<< orphan*/  KC_EQL ; 
 scalar_t__ KC_ESC ; 
 int /*<<< orphan*/  KC_MINS ; 
 int /*<<< orphan*/  KC_QUOT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_S ; 
 int /*<<< orphan*/  KC_SPC ; 
 scalar_t__ KC_T ; 
 int /*<<< orphan*/  KC_Y ; 
 int /*<<< orphan*/  ang_tap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ biton32 (unsigned long) ; 
 int /*<<< orphan*/  clear_oneshot_mods () ; 
 scalar_t__ get_oneshot_mods () ; 
 int /*<<< orphan*/  has_oneshot_mods_timed_out () ; 
 scalar_t__ is_adore ; 
 scalar_t__* last4 ; 
 int /*<<< orphan*/  layer_off (unsigned long) ; 
 unsigned long layer_state ; 
 scalar_t__ log_enable ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 scalar_t__ time_travel ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
#if KEYLOGGER_ENABLE
  if (log_enable) {
    uint8_t layer = biton32(layer_state);

    if ((layer == ADORE) || (layer == BASE))
      uprintf ("KL: col=%02d, row=%02d, pressed=%d, layer=%s\n", record->event.key.col,
               record->event.key.row, record->event.pressed, (is_adore) ? "ADORE" : "Dvorak");
  }
#endif

  if (keycode == KC_ESC && record->event.pressed) {
    bool queue = true;

    if ((get_oneshot_mods ()) && !has_oneshot_mods_timed_out ()) {
      clear_oneshot_mods ();
      queue = false;
    }
    if (layer_state & (1UL<<HUN)) {
      layer_off (HUN);
      queue = false;
    }
    return queue;
  }

  if (time_travel && !record->event.pressed) {
    uint8_t p;

    // shift cache one to the left
    for (p = 0; p < 3; p++) {
      last4[p] = last4[p + 1];
    }
    last4[3] = keycode;

    if (last4[0] == KC_D && last4[1] == KC_A && last4[2] == KC_T && last4[3] == KC_E) {
      ang_tap (KC_E, KC_SPC, KC_MINS, KC_D, KC_SPC, KC_QUOT, 0);
      register_code (KC_RSFT);
      register_code (KC_EQL);
      unregister_code (KC_EQL);
      unregister_code (KC_RSFT);

      ang_tap (KC_4, KC_SPC, KC_D, KC_A, KC_Y, KC_S, KC_QUOT, 0);

      return false;
    }
  }

  return true;
}