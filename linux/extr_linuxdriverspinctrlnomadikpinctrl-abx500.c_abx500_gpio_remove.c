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
struct abx500_pinctrl {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct abx500_pinctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int abx500_gpio_remove(struct platform_device *pdev)
{
	struct abx500_pinctrl *pct = platform_get_drvdata(pdev);

	gpiochip_remove(&pct->chip);
	return 0;
}