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
struct platform_device {int dummy; } ;
struct atmel_hlcdc_pwm {TYPE_1__* hlcdc; int /*<<< orphan*/  chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  periph_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct atmel_hlcdc_pwm* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_hlcdc_pwm_remove(struct platform_device *pdev)
{
	struct atmel_hlcdc_pwm *chip = platform_get_drvdata(pdev);
	int ret;

	ret = pwmchip_remove(&chip->chip);
	if (ret)
		return ret;

	clk_disable_unprepare(chip->hlcdc->periph_clk);

	return 0;
}