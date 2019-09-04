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
struct pwm_device {void* chip_data; } ;

/* Variables and functions */

void *pwm_get_chip_data(struct pwm_device *pwm)
{
	return pwm ? pwm->chip_data : NULL;
}