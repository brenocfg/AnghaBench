#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int dummy; } ;
struct mtk_disp_pwm {int /*<<< orphan*/  clk_main; int /*<<< orphan*/  clk_mm; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct mtk_disp_pwm* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_disp_pwm_remove(struct platform_device *pdev)
{
	struct mtk_disp_pwm *mdp = platform_get_drvdata(pdev);
	int ret;

	ret = pwmchip_remove(&mdp->chip);
	clk_unprepare(mdp->clk_mm);
	clk_unprepare(mdp->clk_main);

	return ret;
}