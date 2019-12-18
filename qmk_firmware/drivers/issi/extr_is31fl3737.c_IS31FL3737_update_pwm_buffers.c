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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS31FL3737_write_pwm_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS31FL3737_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSI_COMMANDREGISTER ; 
 int /*<<< orphan*/  ISSI_COMMANDREGISTER_WRITELOCK ; 
 int ISSI_PAGE_PWM ; 
 int /*<<< orphan*/ * g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3737_update_pwm_buffers(uint8_t addr1, uint8_t addr2) {
    if (g_pwm_buffer_update_required) {
        // Firstly we need to unlock the command register and select PG1
        IS31FL3737_write_register(addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3737_write_register(addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

        IS31FL3737_write_pwm_buffer(addr1, g_pwm_buffer[0]);
        // IS31FL3737_write_pwm_buffer( addr2, g_pwm_buffer[1] );
    }
    g_pwm_buffer_update_required = false;
}