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
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  M_LAYER1 129 
#define  M_LAYER2 128 
 int /*<<< orphan*/  breathing_enable () ; 
 int /*<<< orphan*/  breathing_period_set (int) ; 
 int /*<<< orphan*/  breathing_pulse () ; 
 int /*<<< orphan*/  breathing_self_disable () ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch (id)
    {
    case M_LAYER1:
        // need to add a timer for doubletap: https://github.com/jackhumbert/qmk_firmware/wiki#timer-functionality
        // action_function_tap may also handle this...
        if (record->event.pressed)
        {
            breathing_period_set(3);
            breathing_enable();
            layer_on(1);
        }
        else
        {
            breathing_period_set(1);
            breathing_self_disable();
            layer_off(1);
        }
        break;
    case M_LAYER2:
        if (record->event.pressed)
        {
            breathing_period_set(2);
            breathing_pulse();
            layer_on(2);
        }
        else
        {
            breathing_period_set(1);
            breathing_self_disable();
            layer_off(2);
        }
        break;
    }
    return MACRO_NONE;
}