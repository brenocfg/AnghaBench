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
#define  ARROW 132 
#define  LOWER 131 
#define  NUMPAD 130 
#define  QWERTY 129 
#define  RAISE 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _ARROW ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _NUMPAD ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case QWERTY:
            if (record->event.pressed) {
                layer_off(_ARROW);
                layer_off(_NUMPAD);
            }
            return false;
        case ARROW:
            if (record->event.pressed) {
                layer_off(_NUMPAD);
                layer_on(_ARROW);
            }
            return false;
        case NUMPAD:
            if (record->event.pressed) {
                layer_off(_ARROW);
                layer_on(_NUMPAD);
            }
            return false;
    }
    return true;
}