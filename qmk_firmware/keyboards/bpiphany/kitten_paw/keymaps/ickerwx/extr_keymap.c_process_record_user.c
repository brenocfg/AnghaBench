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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ KC_A ; 
 scalar_t__ KC_BSLS ; 
 scalar_t__ KC_EXSEL ; 
 scalar_t__ KC_GRV ; 
 scalar_t__ KC_NONUS_BSLASH ; 
 scalar_t__ KC_RBRC ; 
 int /*<<< orphan*/  MOD_LSFT ; 
 scalar_t__ PROG2 ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer;
    layer = biton32(layer_state);
    if (layer == PROG2) {
         if (keycode >= KC_A && keycode <= KC_EXSEL && \
             !(  // do not send LSFT + these keycodes, they are needed for emulating the US layout
                 keycode == KC_NONUS_BSLASH ||
                 keycode == KC_RBRC ||
                 keycode == KC_BSLS ||
                 keycode == KC_GRV
            )) {
              // LSFT is the modifier for this layer, so we set LSFT for every key to get the expected behavior
              if (record->event.pressed) {
                  register_mods(MOD_LSFT);
              } else {
                  unregister_mods(MOD_LSFT);
              }
         }
    }
    return true;
}