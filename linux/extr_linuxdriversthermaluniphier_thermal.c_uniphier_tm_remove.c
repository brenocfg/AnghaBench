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
struct uniphier_tm_dev {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct uniphier_tm_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uniphier_tm_disable_sensor (struct uniphier_tm_dev*) ; 

__attribute__((used)) static int uniphier_tm_remove(struct platform_device *pdev)
{
	struct uniphier_tm_dev *tdev = platform_get_drvdata(pdev);

	/* disable sensor */
	uniphier_tm_disable_sensor(tdev);

	return 0;
}