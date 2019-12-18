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
typedef  int uint8_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
typedef  int int8_t ;

/* Variables and functions */
 int KC_ESCAPE ; 
 int KC_GRAVE ; 
 int /*<<< orphan*/  KC_LSHIFT ; 
 int /*<<< orphan*/  KC_RSHIFT ; 
#define  LFK_CLEAR 135 
#define  LFK_CLICK_FREQ_HIGHER 134 
#define  LFK_CLICK_FREQ_LOWER 133 
#define  LFK_CLICK_TIME_LONGER 132 
#define  LFK_CLICK_TIME_SHORTER 131 
#define  LFK_CLICK_TOGGLE 130 
 int LFK_ESC_TILDE ; 
#define  LFK_LED_TEST 129 
#define  LFK_SET_DEFAULT_LAYER 128 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 void add_key (int) ; 
 int /*<<< orphan*/  click (int,int) ; 
 int click_hz ; 
 int click_time ; 
 int click_toggle ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 
 void del_key (int) ; 
 int /*<<< orphan*/  eeconfig_update_default_layer (unsigned long) ; 
 int get_mods () ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  led_test () ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
#ifdef AUDIO_ENABLE
    int8_t sign = 1;
#endif
    if(id == LFK_ESC_TILDE){
        // Send ~ on shift-esc
        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        method(shifted ? KC_GRAVE : KC_ESCAPE);
        send_keyboard_report();
    }else if(event->event.pressed){
        switch(id){
            case LFK_SET_DEFAULT_LAYER:
                // set/save the current base layer to eeprom, falls through to LFK_CLEAR
                eeconfig_update_default_layer(1UL << opt);
                default_layer_set(1UL << opt);
            case LFK_CLEAR:
                // Go back to default layer
                layer_clear();
                break;
#ifdef ISSI_ENABLE
            case LFK_LED_TEST:
                led_test();
                break;
#endif
#ifdef AUDIO_ENABLE
            case LFK_CLICK_FREQ_LOWER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_FREQ_HIGHER:
                click_hz += sign * 100;
                click(click_hz, click_time);
                break;
            case LFK_CLICK_TOGGLE:
                if(click_toggle){
                    click_toggle = 0;
                    click(4000, 100);
                    click(1000, 100);
                }else{
                    click_toggle = 1;
                    click(1000, 100);
                    click(4000, 100);
                }
                break;
            case LFK_CLICK_TIME_SHORTER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_TIME_LONGER:
                click_time += sign;
                click(click_hz, click_time);
                break;
#endif
        }
    }
}