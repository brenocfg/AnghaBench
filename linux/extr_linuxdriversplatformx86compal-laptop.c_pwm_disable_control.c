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
 int /*<<< orphan*/  PWM_DISABLE_ADDR ; 
 unsigned char PWM_DISABLE_DATA ; 
 int /*<<< orphan*/  ec_transaction (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_disable_control(void)
{
	unsigned char writeData = PWM_DISABLE_DATA;
	ec_transaction(PWM_DISABLE_ADDR, &writeData, 1, NULL, 0);
}