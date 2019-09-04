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
 int /*<<< orphan*/  PWM_ADDRESS ; 
 int /*<<< orphan*/  ec_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pwm_lookup_table ; 

__attribute__((used)) static void set_pwm(int pwm)
{
	ec_transaction(PWM_ADDRESS, &pwm_lookup_table[pwm], 1, NULL, 0);
}