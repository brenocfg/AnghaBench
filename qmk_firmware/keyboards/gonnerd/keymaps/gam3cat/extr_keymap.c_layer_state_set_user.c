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
#define  _AL 134 
#define  _BL 133 
#define  _CL 132 
#define  _DL 131 
#define  _FL 130 
#define  _NL 129 
#define  _WL 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_backlight_level (int) ; 

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case _BL:
            custom_backlight_level(0);
            break;
        case _WL:
        case _NL:
        case _DL:
        case _CL:
            custom_backlight_level(1);
            break;
        case _FL:
            custom_backlight_level(2);
            break;
        case _AL:
            custom_backlight_level(3);
            break;
        default:
            custom_backlight_level(0);
            break;
    }
    return state;
}