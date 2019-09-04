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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fsl_pwm_chip {TYPE_1__ chip; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long fsl_pwm_calculate_cycles (struct fsl_pwm_chip*,unsigned long) ; 
 int fsl_pwm_calculate_default_ps (struct fsl_pwm_chip*,int) ; 

__attribute__((used)) static unsigned long fsl_pwm_calculate_period_cycles(struct fsl_pwm_chip *fpc,
						     unsigned long period_ns,
						     enum fsl_pwm_clk index)
{
	int ret;

	ret = fsl_pwm_calculate_default_ps(fpc, index);
	if (ret) {
		dev_err(fpc->chip.dev,
			"failed to calculate default prescaler: %d\n",
			ret);
		return 0;
	}

	return fsl_pwm_calculate_cycles(fpc, period_ns);
}