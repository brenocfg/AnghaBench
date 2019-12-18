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
 unsigned long _PP ; 
 unsigned long _PPG ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  backlight_toggle () ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 

void enable_gaming_layer(void) {
    default_layer_set((1UL << _PP) | (1UL << _PPG));
#ifdef BACKLIGHT_ENABLE
    backlight_toggle();
    _delay_ms(100);
    backlight_toggle();
#endif
}