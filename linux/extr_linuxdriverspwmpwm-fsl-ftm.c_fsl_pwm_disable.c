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
typedef  int u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct fsl_pwm_chip {size_t cnt_select; int /*<<< orphan*/  lock; scalar_t__ period_ns; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 size_t FSL_PWM_CLK_CNTEN ; 
 int /*<<< orphan*/  FTM_OUTMASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_pwm_chip* to_fsl_chip (struct pwm_chip*) ; 

__attribute__((used)) static void fsl_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);
	u32 val;

	mutex_lock(&fpc->lock);
	regmap_update_bits(fpc->regmap, FTM_OUTMASK, BIT(pwm->hwpwm),
			   BIT(pwm->hwpwm));

	clk_disable_unprepare(fpc->clk[FSL_PWM_CLK_CNTEN]);
	clk_disable_unprepare(fpc->clk[fpc->cnt_select]);

	regmap_read(fpc->regmap, FTM_OUTMASK, &val);
	if ((val & 0xFF) == 0xFF)
		fpc->period_ns = 0;

	mutex_unlock(&fpc->lock);
}