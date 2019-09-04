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
 int /*<<< orphan*/  EEEPC_EC_FAN_PWM ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int) ; 
 int eeepc_lmsensors_to_pwm (int) ; 

__attribute__((used)) static void eeepc_set_fan_pwm(int value)
{
	value = eeepc_lmsensors_to_pwm(value);
	ec_write(EEEPC_EC_FAN_PWM, value);
}