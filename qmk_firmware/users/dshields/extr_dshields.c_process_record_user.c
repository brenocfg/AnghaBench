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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ KC_ESC ; 
 int /*<<< orphan*/  clear_oneshot_locked_mods () ; 
 int /*<<< orphan*/  clear_oneshot_mods () ; 
 int /*<<< orphan*/  get_oneshot_locked_mods () ; 
 int /*<<< orphan*/  get_oneshot_mods () ; 
 int /*<<< orphan*/  has_oneshot_mods_timed_out () ; 
 scalar_t__ is_oneshot_layer_active () ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ESC && record->event.pressed) {
        bool rc = true;
        uint8_t mods = 0;
        if ((mods = get_oneshot_mods()) && !has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
            unregister_mods(mods);
            rc = false;
        }
        if ((mods = get_oneshot_locked_mods())) {
            clear_oneshot_locked_mods();
            unregister_mods(mods);
            rc = false;
        }
        if (is_oneshot_layer_active()) {
            layer_clear();
            rc = false;
        }
        return rc;
    }
    return true;
}