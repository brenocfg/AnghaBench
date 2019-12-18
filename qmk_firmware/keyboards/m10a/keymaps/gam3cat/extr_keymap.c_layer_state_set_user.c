#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _L0 137 
#define  _L1 136 
#define  _L2 135 
#define  _L3 134 
#define  _L4 133 
#define  _L5 132 
#define  _L6 131 
#define  _L7 130 
#define  _L8 129 
#define  _L9 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_backlight_level (int) ; 

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case _L0:
            custom_backlight_level(0);
            break;
        case _L1:
            custom_backlight_level(1);
            break;
        case _L2:
            custom_backlight_level(2);
            break;
        case _L3:
            custom_backlight_level(3);
            break;
        case _L4:
            custom_backlight_level(4);
            break;
        case _L5:
            custom_backlight_level(5);
            break;
        case _L6:
            custom_backlight_level(6);
            break;
        case _L7:
            custom_backlight_level(6);
            break;
        case _L8:
            custom_backlight_level(6);
            break;
        case _L9:
            custom_backlight_level(0);
            break;
        default:
            custom_backlight_level(0);
            break;
    }
    return state;
}