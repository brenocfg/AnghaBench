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
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int __cros_ec_pwm_get_duty (struct cros_ec_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_pwm_get_duty(struct cros_ec_device *ec, u8 index)
{
	return __cros_ec_pwm_get_duty(ec, index, NULL);
}