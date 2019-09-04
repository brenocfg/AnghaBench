#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwm_lpss_chip {scalar_t__ regs; int /*<<< orphan*/ * saved_ctrl; TYPE_1__* info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int npwm; } ;

/* Variables and functions */
 scalar_t__ PWM ; 
 int PWM_SIZE ; 
 struct pwm_lpss_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

int pwm_lpss_suspend(struct device *dev)
{
	struct pwm_lpss_chip *lpwm = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < lpwm->info->npwm; i++)
		lpwm->saved_ctrl[i] = readl(lpwm->regs + i * PWM_SIZE + PWM);

	return 0;
}