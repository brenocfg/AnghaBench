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
struct uniphier_aio_chip {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct uniphier_aio_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

int uniphier_aio_remove(struct platform_device *pdev)
{
	struct uniphier_aio_chip *chip = platform_get_drvdata(pdev);

	reset_control_assert(chip->rst);
	clk_disable_unprepare(chip->clk);

	return 0;
}