#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ layer_rgb; } ;

/* Variables and functions */
#define  _BL 131 
#define  _DL 130 
#define  _GL 129 
#define  _UL 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int,int,int) ; 
 TYPE_1__ user_config ; 

uint32_t layer_state_set_user(uint32_t state) {
    // This code switches underglow color by active layer, if the user has enabled the feature
    if(user_config.layer_rgb) {
        switch (biton32(state)) {
            case _BL:
                rgblight_sethsv_noeeprom(0,10,255);
                rgblight_mode_noeeprom(1);
                break;
            case _DL:
                rgblight_sethsv_noeeprom(130,200,255);
                rgblight_mode_noeeprom(1);
                break;
            case _UL:
                rgblight_sethsv_noeeprom(170,200,255);
                rgblight_mode_noeeprom(1);
                break;
            case _GL:
                rgblight_sethsv_noeeprom(0,180,255);
                rgblight_mode_noeeprom(1);
                break;
        }
    }
    return state;
}