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
struct msm_pinctrl {int /*<<< orphan*/  restart_nb; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct msm_pinctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_restart_handler (int /*<<< orphan*/ *) ; 

int msm_pinctrl_remove(struct platform_device *pdev)
{
	struct msm_pinctrl *pctrl = platform_get_drvdata(pdev);

	gpiochip_remove(&pctrl->chip);

	unregister_restart_handler(&pctrl->restart_nb);

	return 0;
}