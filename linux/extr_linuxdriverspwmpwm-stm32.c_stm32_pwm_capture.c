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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct stm32_pwm {unsigned long long max_arr; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; TYPE_1__ chip; } ;
struct pwm_device {int hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct pwm_capture {void* duty_cycle; void* period; } ;

/* Variables and functions */
 void* DIV_ROUND_UP_ULL (unsigned long long,unsigned long) ; 
 int EBUSY ; 
 int EINVAL ; 
 int FIELD_PREP (int,unsigned int) ; 
 unsigned int MAX_TIM_ICPSC ; 
 unsigned int MAX_TIM_PSC ; 
 unsigned long MSEC_PER_SEC ; 
 unsigned long NSEC_PER_MSEC ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CC12P ; 
 int TIM_CCER_CC2P ; 
 int TIM_CCER_CC34P ; 
 int TIM_CCER_CC4P ; 
 int /*<<< orphan*/  TIM_CCMR1 ; 
 int /*<<< orphan*/  TIM_CCMR2 ; 
 int TIM_CCMR_CC1S ; 
 int TIM_CCMR_CC1S_TI1 ; 
 int TIM_CCMR_CC1S_TI2 ; 
 int TIM_CCMR_CC2S ; 
 int TIM_CCMR_CC2S_TI1 ; 
 int TIM_CCMR_CC2S_TI2 ; 
 int TIM_CCMR_IC1PSC ; 
 int TIM_CCMR_IC2PSC ; 
 int /*<<< orphan*/  TIM_PSC ; 
 scalar_t__ active_channels (struct stm32_pwm*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int stm32_pwm_raw_capture (struct stm32_pwm*,struct pwm_device*,unsigned long,int*,int*) ; 
 struct stm32_pwm* to_stm32_pwm_dev (struct pwm_chip*) ; 

__attribute__((used)) static int stm32_pwm_capture(struct pwm_chip *chip, struct pwm_device *pwm,
			     struct pwm_capture *result, unsigned long tmo_ms)
{
	struct stm32_pwm *priv = to_stm32_pwm_dev(chip);
	unsigned long long prd, div, dty;
	unsigned long rate;
	unsigned int psc = 0, icpsc, scale;
	u32 raw_prd = 0, raw_dty = 0;
	int ret = 0;

	mutex_lock(&priv->lock);

	if (active_channels(priv)) {
		ret = -EBUSY;
		goto unlock;
	}

	ret = clk_enable(priv->clk);
	if (ret) {
		dev_err(priv->chip.dev, "failed to enable counter clock\n");
		goto unlock;
	}

	rate = clk_get_rate(priv->clk);
	if (!rate) {
		ret = -EINVAL;
		goto clk_dis;
	}

	/* prescaler: fit timeout window provided by upper layer */
	div = (unsigned long long)rate * (unsigned long long)tmo_ms;
	do_div(div, MSEC_PER_SEC);
	prd = div;
	while ((div > priv->max_arr) && (psc < MAX_TIM_PSC)) {
		psc++;
		div = prd;
		do_div(div, psc + 1);
	}
	regmap_write(priv->regmap, TIM_ARR, priv->max_arr);
	regmap_write(priv->regmap, TIM_PSC, psc);

	/* Map TI1 or TI2 PWM input to IC1 & IC2 (or TI3/4 to IC3 & IC4) */
	regmap_update_bits(priv->regmap,
			   pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2,
			   TIM_CCMR_CC1S | TIM_CCMR_CC2S, pwm->hwpwm & 0x1 ?
			   TIM_CCMR_CC1S_TI2 | TIM_CCMR_CC2S_TI2 :
			   TIM_CCMR_CC1S_TI1 | TIM_CCMR_CC2S_TI1);

	/* Capture period on IC1/3 rising edge, duty cycle on IC2/4 falling. */
	regmap_update_bits(priv->regmap, TIM_CCER, pwm->hwpwm < 2 ?
			   TIM_CCER_CC12P : TIM_CCER_CC34P, pwm->hwpwm < 2 ?
			   TIM_CCER_CC2P : TIM_CCER_CC4P);

	ret = stm32_pwm_raw_capture(priv, pwm, tmo_ms, &raw_prd, &raw_dty);
	if (ret)
		goto stop;

	/*
	 * Got a capture. Try to improve accuracy at high rates:
	 * - decrease counter clock prescaler, scale up to max rate.
	 * - use input prescaler, capture once every /2 /4 or /8 edges.
	 */
	if (raw_prd) {
		u32 max_arr = priv->max_arr - 0x1000; /* arbitrary margin */

		scale = max_arr / min(max_arr, raw_prd);
	} else {
		scale = priv->max_arr; /* bellow resolution, use max scale */
	}

	if (psc && scale > 1) {
		/* 2nd measure with new scale */
		psc /= scale;
		regmap_write(priv->regmap, TIM_PSC, psc);
		ret = stm32_pwm_raw_capture(priv, pwm, tmo_ms, &raw_prd,
					    &raw_dty);
		if (ret)
			goto stop;
	}

	/* Compute intermediate period not to exceed timeout at low rates */
	prd = (unsigned long long)raw_prd * (psc + 1) * NSEC_PER_SEC;
	do_div(prd, rate);

	for (icpsc = 0; icpsc < MAX_TIM_ICPSC ; icpsc++) {
		/* input prescaler: also keep arbitrary margin */
		if (raw_prd >= (priv->max_arr - 0x1000) >> (icpsc + 1))
			break;
		if (prd >= (tmo_ms * NSEC_PER_MSEC) >> (icpsc + 2))
			break;
	}

	if (!icpsc)
		goto done;

	/* Last chance to improve period accuracy, using input prescaler */
	regmap_update_bits(priv->regmap,
			   pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2,
			   TIM_CCMR_IC1PSC | TIM_CCMR_IC2PSC,
			   FIELD_PREP(TIM_CCMR_IC1PSC, icpsc) |
			   FIELD_PREP(TIM_CCMR_IC2PSC, icpsc));

	ret = stm32_pwm_raw_capture(priv, pwm, tmo_ms, &raw_prd, &raw_dty);
	if (ret)
		goto stop;

	if (raw_dty >= (raw_prd >> icpsc)) {
		/*
		 * We may fall here using input prescaler, when input
		 * capture starts on high side (before falling edge).
		 * Example with icpsc to capture on each 4 events:
		 *
		 *       start   1st capture                     2nd capture
		 *         v     v                               v
		 *         ___   _____   _____   _____   _____   ____
		 * TI1..4     |__|    |__|    |__|    |__|    |__|
		 *            v  v    .  .    .  .    .       v  v
		 * icpsc1/3:  .  0    .  1    .  2    .  3    .  0
		 * icpsc2/4:  0       1       2       3       0
		 *            v  v                            v  v
		 * CCR1/3  ......t0..............................t2
		 * CCR2/4  ..t1..............................t1'...
		 *               .                            .  .
		 * Capture0:     .<----------------------------->.
		 * Capture1:     .<-------------------------->.  .
		 *               .                            .  .
		 * Period:       .<------>                    .  .
		 * Low side:                                  .<>.
		 *
		 * Result:
		 * - Period = Capture0 / icpsc
		 * - Duty = Period - Low side = Period - (Capture0 - Capture1)
		 */
		raw_dty = (raw_prd >> icpsc) - (raw_prd - raw_dty);
	}

done:
	prd = (unsigned long long)raw_prd * (psc + 1) * NSEC_PER_SEC;
	result->period = DIV_ROUND_UP_ULL(prd, rate << icpsc);
	dty = (unsigned long long)raw_dty * (psc + 1) * NSEC_PER_SEC;
	result->duty_cycle = DIV_ROUND_UP_ULL(dty, rate);
stop:
	regmap_write(priv->regmap, TIM_CCER, 0);
	regmap_write(priv->regmap, pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2, 0);
	regmap_write(priv->regmap, TIM_PSC, 0);
clk_dis:
	clk_disable(priv->clk);
unlock:
	mutex_unlock(&priv->lock);

	return ret;
}