#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {int alive; size_t led_id; int /*<<< orphan*/  time; } ;
struct TYPE_3__ {size_t WAVE_PERIOD; size_t WAVE_FRONT_WIDTH; scalar_t__ TRAVEL_DISTANCE; int PATTERN_INDEX; } ;

/* Variables and functions */
 int* DISTANCE_FROM_LAST_KEYSTROKE ; 
 scalar_t__** DISTANCE_MAP ; 
 size_t KEY_LED_COUNT ; 
 TYPE_2__* KEY_STROKES ; 
 size_t KEY_STROKES_LENGTH ; 
 TYPE_1__ USER_CONFIG ; 
 size_t timer_elapsed32 (int /*<<< orphan*/ ) ; 

void calculate_keystroke_distance(void){
    bool alive;
    uint8_t led_id, period_passed;
    uint32_t t;


    for(uint8_t i = 0; i <= KEY_LED_COUNT; ++i){
        DISTANCE_FROM_LAST_KEYSTROKE[i] = 0;
    }

    for(uint8_t i = 0; i < KEY_STROKES_LENGTH; ++i){
        if(KEY_STROKES[i].alive){
            t = timer_elapsed32(KEY_STROKES[i].time);
            alive = 0;
            led_id = KEY_STROKES[i].led_id;
            period_passed = t / USER_CONFIG.WAVE_PERIOD;

            uint8_t delta_period;
            for(uint8_t j = 1; j <= KEY_LED_COUNT; ++j){
                delta_period = period_passed - DISTANCE_MAP[led_id][j];
                if(( delta_period < USER_CONFIG.WAVE_FRONT_WIDTH) && (
                    DISTANCE_MAP[led_id][j] <= USER_CONFIG.TRAVEL_DISTANCE
                )){
                    switch(USER_CONFIG.PATTERN_INDEX){
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        DISTANCE_FROM_LAST_KEYSTROKE[j] += delta_period;
                        break;
                    default:
                        DISTANCE_FROM_LAST_KEYSTROKE[j] = 1;
                        break;
                    }
                    alive = 1;
                }
            }
            KEY_STROKES[i].alive = alive;
        }
    }
}