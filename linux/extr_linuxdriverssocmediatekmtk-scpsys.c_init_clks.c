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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int CLK_MAX ; 
 int CLK_NONE ; 
 int /*<<< orphan*/ * clk_names ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_clks(struct platform_device *pdev, struct clk **clk)
{
	int i;

	for (i = CLK_NONE + 1; i < CLK_MAX; i++)
		clk[i] = devm_clk_get(&pdev->dev, clk_names[i]);
}