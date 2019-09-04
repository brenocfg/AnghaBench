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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EEEPC_EC_FAN_PWM ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int eeepc_pwm_to_lmsensors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eeepc_get_fan_pwm(void)
{
	u8 value = 0;

	ec_read(EEEPC_EC_FAN_PWM, &value);
	return eeepc_pwm_to_lmsensors(value);
}