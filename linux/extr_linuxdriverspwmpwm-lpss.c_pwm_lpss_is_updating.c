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
struct pwm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int PWM_SW_UPDATE ; 
 int pwm_lpss_read (struct pwm_device*) ; 

__attribute__((used)) static inline int pwm_lpss_is_updating(struct pwm_device *pwm)
{
	return (pwm_lpss_read(pwm) & PWM_SW_UPDATE) ? -EBUSY : 0;
}