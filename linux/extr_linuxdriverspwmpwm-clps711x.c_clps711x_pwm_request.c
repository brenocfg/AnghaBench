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
struct TYPE_2__ {int /*<<< orphan*/  period; } ;
struct pwm_device {TYPE_1__ args; } ;
struct pwm_chip {int dummy; } ;
struct clps711x_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct clps711x_chip* to_clps711x_chip (struct pwm_chip*) ; 

__attribute__((used)) static int clps711x_pwm_request(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct clps711x_chip *priv = to_clps711x_chip(chip);
	unsigned int freq = clk_get_rate(priv->clk);

	if (!freq)
		return -EINVAL;

	/* Store constant period value */
	pwm->args.period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, freq);

	return 0;
}