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
 int /*<<< orphan*/  I2Cx_EV_IRQn ; 
 int /*<<< orphan*/  MBOOT_I2Cx ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int /*<<< orphan*/  i2c_slave_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_state_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int) ; 
 int /*<<< orphan*/  pyb_usbdd_shutdown () ; 

__attribute__((used)) static void do_reset(void) {
    led_state_all(0);
    mp_hal_delay_ms(50);
    pyb_usbdd_shutdown();
    #if defined(MBOOT_I2C_SCL)
    i2c_slave_shutdown(MBOOT_I2Cx, I2Cx_EV_IRQn);
    #endif
    mp_hal_delay_ms(50);
    NVIC_SystemReset();
}