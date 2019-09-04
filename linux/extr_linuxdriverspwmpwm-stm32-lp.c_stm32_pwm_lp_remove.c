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
struct TYPE_2__ {int /*<<< orphan*/ * pwms; } ;
struct stm32_pwm_lp {TYPE_1__ chip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct stm32_pwm_lp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (TYPE_1__*) ; 

__attribute__((used)) static int stm32_pwm_lp_remove(struct platform_device *pdev)
{
	struct stm32_pwm_lp *priv = platform_get_drvdata(pdev);

	pwm_disable(&priv->chip.pwms[0]);

	return pwmchip_remove(&priv->chip);
}