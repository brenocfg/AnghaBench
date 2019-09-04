#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tpu_pwm_device {int timer_on; int prescaler; int duty; int period; int /*<<< orphan*/  channel; TYPE_2__* tpu; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPU_PIN_INACTIVE ; 
 int /*<<< orphan*/  TPU_PIN_PWM ; 
 int TPU_TCR_CCLR_TGRB ; 
 int TPU_TCR_CKEG_RISING ; 
 int /*<<< orphan*/  TPU_TCRn ; 
 int /*<<< orphan*/  TPU_TGRAn ; 
 int /*<<< orphan*/  TPU_TGRBn ; 
 int TPU_TMDR_MD_PWM ; 
 int /*<<< orphan*/  TPU_TMDRn ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpu_pwm_set_pin (struct tpu_pwm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpu_pwm_start_stop (struct tpu_pwm_device*,int) ; 
 int /*<<< orphan*/  tpu_pwm_write (struct tpu_pwm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tpu_pwm_timer_start(struct tpu_pwm_device *pwm)
{
	int ret;

	if (!pwm->timer_on) {
		/* Wake up device and enable clock. */
		pm_runtime_get_sync(&pwm->tpu->pdev->dev);
		ret = clk_prepare_enable(pwm->tpu->clk);
		if (ret) {
			dev_err(&pwm->tpu->pdev->dev, "cannot enable clock\n");
			return ret;
		}
		pwm->timer_on = true;
	}

	/*
	 * Make sure the channel is stopped, as we need to reconfigure it
	 * completely. First drive the pin to the inactive state to avoid
	 * glitches.
	 */
	tpu_pwm_set_pin(pwm, TPU_PIN_INACTIVE);
	tpu_pwm_start_stop(pwm, false);

	/*
	 * - Clear TCNT on TGRB match
	 * - Count on rising edge
	 * - Set prescaler
	 * - Output 0 until TGRA, output 1 until TGRB (active low polarity)
	 * - Output 1 until TGRA, output 0 until TGRB (active high polarity
	 * - PWM mode
	 */
	tpu_pwm_write(pwm, TPU_TCRn, TPU_TCR_CCLR_TGRB | TPU_TCR_CKEG_RISING |
		      pwm->prescaler);
	tpu_pwm_write(pwm, TPU_TMDRn, TPU_TMDR_MD_PWM);
	tpu_pwm_set_pin(pwm, TPU_PIN_PWM);
	tpu_pwm_write(pwm, TPU_TGRAn, pwm->duty);
	tpu_pwm_write(pwm, TPU_TGRBn, pwm->period);

	dev_dbg(&pwm->tpu->pdev->dev, "%u: TGRA 0x%04x TGRB 0x%04x\n",
		pwm->channel, pwm->duty, pwm->period);

	/* Start the channel. */
	tpu_pwm_start_stop(pwm, true);

	return 0;
}