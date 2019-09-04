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
typedef  int u8 ;
struct samsung_pwm_variant {int bits; int div_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct samsung_pwm_chip {TYPE_1__ chip; struct clk* tclk1; struct clk* tclk0; struct samsung_pwm_variant variant; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned long pwm_samsung_get_tin_rate (struct samsung_pwm_chip*,unsigned int) ; 
 int /*<<< orphan*/  pwm_samsung_is_tdiv (struct samsung_pwm_chip*,unsigned int) ; 
 int /*<<< orphan*/  pwm_samsung_set_divisor (struct samsung_pwm_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pwm_samsung_calc_tin(struct samsung_pwm_chip *chip,
					  unsigned int chan, unsigned long freq)
{
	struct samsung_pwm_variant *variant = &chip->variant;
	unsigned long rate;
	struct clk *clk;
	u8 div;

	if (!pwm_samsung_is_tdiv(chip, chan)) {
		clk = (chan < 2) ? chip->tclk0 : chip->tclk1;
		if (!IS_ERR(clk)) {
			rate = clk_get_rate(clk);
			if (rate)
				return rate;
		}

		dev_warn(chip->chip.dev,
			"tclk of PWM %d is inoperational, using tdiv\n", chan);
	}

	rate = pwm_samsung_get_tin_rate(chip, chan);
	dev_dbg(chip->chip.dev, "tin parent at %lu\n", rate);

	/*
	 * Compare minimum PWM frequency that can be achieved with possible
	 * divider settings and choose the lowest divisor that can generate
	 * frequencies lower than requested.
	 */
	if (variant->bits < 32) {
		/* Only for s3c24xx */
		for (div = variant->div_base; div < 4; ++div)
			if ((rate >> (variant->bits + div)) < freq)
				break;
	} else {
		/*
		 * Other variants have enough counter bits to generate any
		 * requested rate, so no need to check higher divisors.
		 */
		div = variant->div_base;
	}

	pwm_samsung_set_divisor(chip, chan, BIT(div));

	return rate >> div;
}