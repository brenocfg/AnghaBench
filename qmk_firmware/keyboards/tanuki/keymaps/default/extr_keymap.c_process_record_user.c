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
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int layer_rgb; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
#define  CUSTRGB 134 
#define  RGB_HUI 133 
#define  RGB_MOD 132 
#define  RGB_SAD 131 
#define  RGB_SAI 130 
#define  RGB_VAD 129 
#define  RGB_VAI 128 
 int /*<<< orphan*/  eeconfig_update_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  layer_state_set (int /*<<< orphan*/ ) ; 
 TYPE_3__ user_config ; 

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CUSTRGB: // if the user toggled per-layer RGB, update the config and refresh the RGB color
            if(record->event.pressed) {
                user_config.layer_rgb ^= 1;
                eeconfig_update_user(user_config.raw);
                if (user_config.layer_rgb) {
                    layer_state_set(layer_state);
                }
            }
            return false;
            break;
        case RGB_MOD:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_HUI:
        case RGB_VAD:
        case RGB_VAI:
            if(user_config.layer_rgb && record->event.pressed) {
                return false; // if layer RGB is on, ignore attempts to change RGB settings
            }
            break;
    }
    return true;
}