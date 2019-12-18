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
 int /*<<< orphan*/  IS31FL3736_update_pwm_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSI_ADDR_DEFAULT ; 

void backlight_update_pwm_buffers(void)
{
	IS31FL3736_update_pwm_buffers(ISSI_ADDR_DEFAULT,0x00);
}