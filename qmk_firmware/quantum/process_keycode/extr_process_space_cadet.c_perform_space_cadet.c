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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ IS_MOD (scalar_t__) ; 
 int /*<<< orphan*/  MOD_BIT (scalar_t__) ; 
 scalar_t__ TAPPING_TERM ; 
 int /*<<< orphan*/  clear_weak_mods () ; 
 int /*<<< orphan*/  get_mods () ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 scalar_t__ sc_last ; 
 int /*<<< orphan*/  sc_mods ; 
 int /*<<< orphan*/  sc_timer ; 
 int /*<<< orphan*/  set_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (scalar_t__) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

void perform_space_cadet(keyrecord_t *record, uint8_t holdMod, uint8_t tapMod, uint8_t keycode) {
    if (record->event.pressed) {
        sc_last  = holdMod;
        sc_timer = timer_read();
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
        sc_mods = get_mods();
#endif
        if (IS_MOD(holdMod)) {
            register_mods(MOD_BIT(holdMod));
        }
    } else {
        if (sc_last == holdMod && timer_elapsed(sc_timer) < TAPPING_TERM) {
            if (holdMod != tapMod) {
                if (IS_MOD(holdMod)) {
                    unregister_mods(MOD_BIT(holdMod));
                }
                if (IS_MOD(tapMod)) {
                    register_mods(MOD_BIT(tapMod));
                }
            }
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
            set_weak_mods(sc_mods);
#endif
            tap_code(keycode);
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
            clear_weak_mods();
#endif
            if (IS_MOD(tapMod)) {
                unregister_mods(MOD_BIT(tapMod));
            }
        } else {
            if (IS_MOD(holdMod)) {
                unregister_mods(MOD_BIT(holdMod));
            }
        }
    }
}