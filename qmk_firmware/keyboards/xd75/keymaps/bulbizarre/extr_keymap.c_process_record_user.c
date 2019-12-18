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
#define  SWITCH_FN 129 
#define  SWITCH_FS 128 
 int /*<<< orphan*/  _FN ; 
 int /*<<< orphan*/  _FS ; 
 int /*<<< orphan*/  gp100_led_off () ; 
 int /*<<< orphan*/  gp100_led_on () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lt12_timer ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SWITCH_FN:
        if (record->event.pressed) {
            lt12_timer = timer_read();
            layer_on(_FN);
            gp100_led_on();
        } else {
            if (timer_elapsed(lt12_timer) > 200) {  
            layer_off(_FN);
            gp100_led_off();
            }
        }
        return false;
        break;
        case SWITCH_FS:
        if (record->event.pressed) {
            lt12_timer = timer_read();
            layer_on(_FS);
            gp100_led_on();
        } else {
            if (timer_elapsed(lt12_timer) > 200) {  
            layer_off(_FS);
            gp100_led_off();
            }
        }
        return false;
        break;
    }
    return true;
}