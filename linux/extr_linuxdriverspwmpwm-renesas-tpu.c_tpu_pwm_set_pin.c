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
struct tpu_pwm_device {int /*<<< orphan*/  polarity; int /*<<< orphan*/  channel; TYPE_2__* tpu; } ;
typedef  enum tpu_pin_state { ____Placeholder_tpu_pin_state } tpu_pin_state ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_POLARITY_INVERSED ; 
#define  TPU_PIN_ACTIVE 130 
#define  TPU_PIN_INACTIVE 129 
#define  TPU_PIN_PWM 128 
 int /*<<< orphan*/  TPU_TIOR_IOA_0 ; 
 int /*<<< orphan*/  TPU_TIOR_IOA_0_SET ; 
 int /*<<< orphan*/  TPU_TIOR_IOA_1 ; 
 int /*<<< orphan*/  TPU_TIOR_IOA_1_CLR ; 
 int /*<<< orphan*/  TPU_TIORn ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  tpu_pwm_write (struct tpu_pwm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tpu_pwm_set_pin(struct tpu_pwm_device *pwm,
			    enum tpu_pin_state state)
{
	static const char * const states[] = { "inactive", "PWM", "active" };

	dev_dbg(&pwm->tpu->pdev->dev, "%u: configuring pin as %s\n",
		pwm->channel, states[state]);

	switch (state) {
	case TPU_PIN_INACTIVE:
		tpu_pwm_write(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_1 : TPU_TIOR_IOA_0);
		break;
	case TPU_PIN_PWM:
		tpu_pwm_write(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_0_SET : TPU_TIOR_IOA_1_CLR);
		break;
	case TPU_PIN_ACTIVE:
		tpu_pwm_write(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_0 : TPU_TIOR_IOA_1);
		break;
	}
}