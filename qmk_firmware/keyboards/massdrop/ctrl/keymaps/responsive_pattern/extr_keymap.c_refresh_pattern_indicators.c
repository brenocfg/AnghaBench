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
typedef  int uint8_t ;
struct TYPE_2__ {int PATTERN_INDEX; } ;

/* Variables and functions */
#define  KC_1 134 
#define  KC_2 133 
#define  KC_3 132 
#define  KC_4 131 
#define  KC_5 130 
#define  KC_6 129 
#define  KC_GRV 128 
 TYPE_1__ USER_CONFIG ; 
 int /*<<< orphan*/  ktli (int) ; 
 int layer_state ; 
 int /*<<< orphan*/  set_indicator_led_rgb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  unset_indicator_led_rgb (int /*<<< orphan*/ ,int) ; 

void refresh_pattern_indicators(void){
    static uint8_t GRV_123456[] = {
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
    };

    if(layer_state >= 0x04){
        for(uint8_t i = 0; i < 7; ++i){
            if(i == USER_CONFIG.PATTERN_INDEX){
                set_indicator_led_rgb(ktli(GRV_123456[i]), 2, 0, 0, 255);
            } else{
                set_indicator_led_rgb(ktli(GRV_123456[i]), 2, 0, 255, 0);
            }
        }
    } else{
        for(uint8_t i = 0; i < 7; ++i){
            unset_indicator_led_rgb(ktli(GRV_123456[i]), 2);
        }
    }
}