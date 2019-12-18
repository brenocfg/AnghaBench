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
 int /*<<< orphan*/  I2C3733_Control_Set (int) ; 
 scalar_t__ led_enabled ; 
 int /*<<< orphan*/  suspend_wakeup_init_kb () ; 

void suspend_wakeup_init(void) {
#ifdef RGB_MATRIX_ENABLE
#    ifdef USE_MASSDROP_CONFIGURATOR
    if (led_enabled) {
        I2C3733_Control_Set(1);
    }
#    else
    I2C3733_Control_Set(1);
#    endif
#endif

    suspend_wakeup_init_kb();
}