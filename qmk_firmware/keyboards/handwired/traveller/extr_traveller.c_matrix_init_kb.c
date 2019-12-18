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

/* Variables and functions */
 int DDRC ; 
 int PORTC ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  rgblight_init () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void matrix_init_kb(void) {
        // put your keyboard start-up code here
        // runs once when the firmware starts up

#ifdef RGBLIGHT_ENABLE
        rgblight_init();
        rgblight_mode(1); // solid, no timer
        rgblight_setrgb(0,20,0);// dim green, happens to be same as _QW
#endif

// Turn status LED on
        DDRC |= (1<<7);
        PORTC |= (1<<7);

        matrix_init_user();
}