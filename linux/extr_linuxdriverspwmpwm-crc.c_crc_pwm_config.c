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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;
struct crystalcove_pwm {int /*<<< orphan*/  regmap; TYPE_1__ chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM0_CLK_DIV ; 
 int /*<<< orphan*/  PWM0_DUTY_CYCLE ; 
 int PWM_BASE_CLK ; 
 int PWM_MAX_LEVEL ; 
 int PWM_MAX_PERIOD_NS ; 
 int PWM_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  crc_pwm_disable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  crc_pwm_enable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int pwm_get_period (struct pwm_device*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct crystalcove_pwm* to_crc_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int crc_pwm_config(struct pwm_chip *c, struct pwm_device *pwm,
			  int duty_ns, int period_ns)
{
	struct crystalcove_pwm *crc_pwm = to_crc_pwm(c);
	struct device *dev = crc_pwm->chip.dev;
	int level;

	if (period_ns > PWM_MAX_PERIOD_NS) {
		dev_err(dev, "un-supported period_ns\n");
		return -EINVAL;
	}

	if (pwm_get_period(pwm) != period_ns) {
		int clk_div;

		/* changing the clk divisor, need to disable fisrt */
		crc_pwm_disable(c, pwm);
		clk_div = PWM_BASE_CLK * period_ns / NSEC_PER_SEC;

		regmap_write(crc_pwm->regmap, PWM0_CLK_DIV,
					clk_div | PWM_OUTPUT_ENABLE);

		/* enable back */
		crc_pwm_enable(c, pwm);
	}

	/* change the pwm duty cycle */
	level = duty_ns * PWM_MAX_LEVEL / period_ns;
	regmap_write(crc_pwm->regmap, PWM0_DUTY_CYCLE, level);

	return 0;
}