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
struct pwm_lpss_chip {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

int pwm_lpss_remove(struct pwm_lpss_chip *lpwm)
{
	return pwmchip_remove(&lpwm->chip);
}