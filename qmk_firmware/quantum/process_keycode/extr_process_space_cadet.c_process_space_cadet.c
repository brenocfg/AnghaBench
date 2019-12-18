#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  KC_LAPO 134 
#define  KC_LCPO 133 
#define  KC_LSPO 132 
#define  KC_RAPC 131 
#define  KC_RCPC 130 
#define  KC_RSPC 129 
#define  KC_SFTENT 128 
 int /*<<< orphan*/  LAPO_KEYS ; 
 int /*<<< orphan*/  LCPO_KEYS ; 
 int /*<<< orphan*/  LSPO_KEYS ; 
 int /*<<< orphan*/  RAPC_KEYS ; 
 int /*<<< orphan*/  RCPC_KEYS ; 
 int /*<<< orphan*/  RSPC_KEYS ; 
 int /*<<< orphan*/  SFTENT_KEYS ; 
 int /*<<< orphan*/  perform_space_cadet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_last ; 

bool process_space_cadet(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSPO: {
            perform_space_cadet(record, LSPO_KEYS);
            return false;
        }
        case KC_RSPC: {
            perform_space_cadet(record, RSPC_KEYS);
            return false;
        }
        case KC_LCPO: {
            perform_space_cadet(record, LCPO_KEYS);
            return false;
        }
        case KC_RCPC: {
            perform_space_cadet(record, RCPC_KEYS);
            return false;
        }
        case KC_LAPO: {
            perform_space_cadet(record, LAPO_KEYS);
            return false;
        }
        case KC_RAPC: {
            perform_space_cadet(record, RAPC_KEYS);
            return false;
        }
        case KC_SFTENT: {
            perform_space_cadet(record, SFTENT_KEYS);
            return false;
        }
        default: {
            if (record->event.pressed) {
                sc_last = 0;
            }
            break;
        }
    }
    return true;
}