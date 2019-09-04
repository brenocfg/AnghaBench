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
struct atmel_tcb_pwm_chip {TYPE_1__* tc; int /*<<< orphan*/  chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  slow_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_tc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct atmel_tcb_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_tcb_pwm_remove(struct platform_device *pdev)
{
	struct atmel_tcb_pwm_chip *tcbpwm = platform_get_drvdata(pdev);
	int err;

	clk_disable_unprepare(tcbpwm->tc->slow_clk);

	err = pwmchip_remove(&tcbpwm->chip);
	if (err < 0)
		return err;

	atmel_tc_free(tcbpwm->tc);

	return 0;
}