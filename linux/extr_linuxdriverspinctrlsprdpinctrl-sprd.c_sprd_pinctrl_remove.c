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
struct sprd_pinctrl {int /*<<< orphan*/  pctl; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_unregister (int /*<<< orphan*/ ) ; 
 struct sprd_pinctrl* platform_get_drvdata (struct platform_device*) ; 

int sprd_pinctrl_remove(struct platform_device *pdev)
{
	struct sprd_pinctrl *sprd_pctl = platform_get_drvdata(pdev);

	pinctrl_unregister(sprd_pctl->pctl);
	return 0;
}