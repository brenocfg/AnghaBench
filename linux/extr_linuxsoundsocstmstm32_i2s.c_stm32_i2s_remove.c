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
struct stm32_i2s_data {int /*<<< orphan*/  pclk; int /*<<< orphan*/  i2sclk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct stm32_i2s_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stm32_i2s_remove(struct platform_device *pdev)
{
	struct stm32_i2s_data *i2s = platform_get_drvdata(pdev);

	clk_disable_unprepare(i2s->i2sclk);
	clk_disable_unprepare(i2s->pclk);

	return 0;
}