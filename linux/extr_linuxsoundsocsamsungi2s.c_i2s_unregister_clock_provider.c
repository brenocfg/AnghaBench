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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct i2s_dai {int dummy; } ;

/* Variables and functions */
 struct i2s_dai* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  i2s_unregister_clocks (struct i2s_dai*) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2s_unregister_clock_provider(struct platform_device *pdev)
{
	struct i2s_dai *i2s = dev_get_drvdata(&pdev->dev);

	of_clk_del_provider(pdev->dev.of_node);
	i2s_unregister_clocks(i2s);
}