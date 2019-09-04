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
struct TYPE_4__ {int /*<<< orphan*/ * pwms; } ;
struct sti_pwm_chip {TYPE_2__ chip; int /*<<< orphan*/  cpt_clk; int /*<<< orphan*/  pwm_clk; TYPE_1__* cdata; } ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {unsigned int pwm_num_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct sti_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (TYPE_2__*) ; 

__attribute__((used)) static int sti_pwm_remove(struct platform_device *pdev)
{
	struct sti_pwm_chip *pc = platform_get_drvdata(pdev);
	unsigned int i;

	for (i = 0; i < pc->cdata->pwm_num_devs; i++)
		pwm_disable(&pc->chip.pwms[i]);

	clk_unprepare(pc->pwm_clk);
	clk_unprepare(pc->cpt_clk);

	return pwmchip_remove(&pc->chip);
}