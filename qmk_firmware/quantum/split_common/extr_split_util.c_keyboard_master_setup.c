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
 int /*<<< orphan*/  matrix_master_OLED_init () ; 
 int /*<<< orphan*/  transport_master_init () ; 

__attribute__((used)) static void keyboard_master_setup(void) {
#if defined(USE_I2C) || defined(EH)
#    ifdef SSD1306OLED
    matrix_master_OLED_init();
#    endif
#endif
    transport_master_init();
}